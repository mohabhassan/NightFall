#viewmodelanim changed
import subprocess
from pathlib import Path
import time
from threading  import Thread, Event
import ctypes

from queue import Queue, Empty
def enqueue_output(out, queue, stop_event):
    while not stop_event.is_set():
        line = out.readline()
        if line == '': break
        queue.put(line)
    #print('worker thread terminated')
    return
    #out.close()

class BotManager():
    """Manages fake client/bot for tests"""
    total_instances = 0
    def __init__(self, rootdir, server_port):
        self.rootdir = rootdir
        self.bot_path = rootdir / 'bot'
        self.exe_path = self.bot_path / 'Network.exe'
        self.server_port = server_port
        self.bot_process = None
        self.connected = False
        self.stdout_thread = None
        self.stdout_thread_stop = None
        self.out_q = None
        self.instance_id = -1
    
    def __del__(self):
        self.disconnect()
    
    def start_bot(self, *args):
        try:
            self.bot_process = subprocess.Popen([self.exe_path.as_posix(), '-t', self.server_port, *args], stdout=subprocess.PIPE, stdin=subprocess.PIPE, cwd=self.bot_path)
            self.out_q = Queue()
            self.stdout_thread_stop = Event()
            self.stdout_thread = Thread(target=enqueue_output, args=(self.bot_process.stdout, self.out_q, self.stdout_thread_stop), daemon=True)
            self.stdout_thread.start()
            self.instance_id = BotManager.total_instances
            BotManager.total_instances += 1
            print('BotManager: start_bot: instance_id:', self.instance_id)
            return True
        except Exception as e:
            self.bot_process = None
            print('BotManager: start_bot error:', str(e))
            print('bot exe path:', self.exe_path)
            return False
    def out_readline(self, block=True):
        try:
            line = self.out_q.get(block) # or q.get(timeout=.1)
        except Empty:
            return None
        else:
            return line
    
    def wait_till_connected(self):
        while self.bot_process is not None:
                line = self.out_readline()
                if not line:
                    print('BotManager: wait_till_connected: error!')
                    break
                
                if line.find(b'client entered world') != -1:
                    print('BotManager: wait_till_connected: connected!')
                    self.connected = True
                    break
    
    def ensure_connected(self):
        if not self.is_connected():
            self.start_bot()
            self.wait_till_connected()

    def send_command(self, cmd, without_delay=False):
        if self.bot_process is not None:
            if not without_delay: time.sleep(1)#avoid sv_floodprotect (client text ignored for mohpc_test)
            try:
                self.bot_process.stdin.write(cmd + b'\r\n')
            except:
                print('BoTManager: send_command exception!')
            if self.bot_process.poll() is None:
                self.bot_process.stdin.flush()
    
    def flush_output(self):
         return
         if self.bot_process is not None:
                self.bot_process.stdout.flush()
                
    #returns True if output is found, false otherwise
    def check_for_output(self, bstr, exact=False):
        if self.bot_process is not None:
                #print('BotManager: check_for_output: reading line...')
                line = self.out_readline()
                if not line:
                    print('BotManager: check_for_output: error!')
                    return False
                
                #print('BotManager: check_for_output: line:', line)
                if not exact and line.find(bstr) != -1:
                    return True
                if exact and line == bstr:
                    return True
        return False
    
    #returns True if output is found, false otherwise
    def wait_for_output(self, bstr):
        while self.bot_process is not None:
                line = self.out_readline()
                if not line:
                    print('BotManager: wait_for_output: error!')
                    return False
                
                if line.find(bstr) != -1:
                    return True
        return False

    #returns True if output is found, false otherwise
    def send_cmd_await_output(self, bcmd, bout, without_delay=False):
        if self.bot_process is None: return False
        self.flush_output()
        #print('BotManager: send_cmd_check_output: flushed output')
        self.send_command(bcmd)
        return self.wait_for_output(bout)
    
    #returns True if outputs are found, false otherwise
    def send_cmd_await_outputs(self, bcmd, bouts, without_delay=False):
        if self.bot_process is None: return False
        self.flush_output()
        self.send_command(bcmd)
        res = True
        for x in bouts:
            res = res and self.wait_for_output(x)
        return res
    
    def stop_stdout_thread(self):
        if self.stdout_thread is not None:
            self.stdout_thread_stop.set()
            #self.stdout_thread.join() # no need to join, thread will close when the process closes
            self.stdout_thread = None
            self.stdout_thread_stop = None
    
    def disconnect(self):
        if self.bot_process is not None:
            if self.bot_process.poll() is None:
                self.send_command(b'disconnect')
            if self.bot_process.poll() is None:
                self.bot_process.wait()
            self.bot_process = None
            self.connected = False
            BotManager.total_instances -= 1
            self.instance_id = -1
        self.stop_stdout_thread()
    
    def stop_bot(self):
        if self.bot_process is not None:
            self.bot_process.terminate()
            self.bot_process = None
            self.connected = False
            BotManager.total_instances -= 1
            self.instance_id = -1
        self.stop_stdout_thread()
    def is_running(self):
        return self.bot_process is not None and self.bot_process.poll() is None
    
    def is_connected(self):
         return self.connected

    def new_instance(self, should_connect=True):
        inst = BotManager(self.rootdir, self.server_port)
        if should_connect: 
            inst.ensure_connected()
        return inst
    
    def new_muliple_instances(self, n, should_connect=True):
        insts = ()
        for i in range(n):
             insts = insts + (self.new_instance(should_connect),)

        return insts

    def spawn(self, team=b'axis'):
        print('BotManager: spawn: team:',  team.decode(), 'instance_id:', self.instance_id)
        self.send_command(b'set dm_playermodel american_army')
        self.send_command(b'set dm_playergermanmodel german_wehrmacht_soldier')
        assert self.instance_id != -1
        assert self.send_cmd_await_output(b'join_team ' + team, b'mohpc_test' + str(self.instance_id).encode() + b' has joined the ' + team.capitalize())
        self.send_command(b'primarydmweapon rifle')
        time.sleep(1) #for spawn
        print('BotManager: spawned:', team.decode())