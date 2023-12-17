import socket
import re
import time

class RCONManager():
    """Hangled rcon communication with game."""
    rcon_ip = 'localhost'
    rcon_password = b'testpw'
    rcon_send_header = b'\xff\xff\xff\xff\02 rcon ' + rcon_password + b' '
    #rcon_recv_header = b'\xff\xff\xff\xff\01print\n'
    def __init__(self, port):
        self.sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        self.sock.settimeout(20)
        self.rcon_port = port
        self.send_delay = 0

    #sends command and returns the response
    def send_command(self, cmd: bytes):
        if self.send_delay > 0:time.sleep(self.send_delay)
        self.sock.sendto(self.rcon_send_header + cmd, (self.rcon_ip, int(self.rcon_port)))
        print('RconManager: send_command cmd:' + str(cmd))
        #print('sent:', self.rcon_send_header + cmd)
        try:
            data, _ = self.sock.recvfrom(65507)
            data = data.decode(errors='ignore')
            #print('data:', data)
            #print('data split:', data.split('\n', maxsplit=1)[1])
            return data.split('\n', maxsplit=1)[1]
        except Exception as e:
            print('RconManager: send_command recvfrom error:' + str(e))
            return None
    
    #keeps executing cmd until it succeeds
    def wait_for_command(self, bcmd):
        while self.send_command(bcmd) is None:
            time.sleep(1)
    
    def send_cmd_check_output(self, bcmd, bout_expected):
        out_actual = self.send_command(bcmd)
        print('RconManager: send_cmd_check_output: out_actual:', out_actual)
        return out_actual.find(bout_expected.decode()) != -1

    def send_cmd_check_outputs(self, bcmd, bouts_expected):
        out_actual = self.send_command(bcmd)
        start = 0
        print('RCONManager: send_cmd_check_outputs: out_actual: ', out_actual)
        for x in bouts_expected:
            find_id = out_actual.find(x.decode(), start)
            if find_id == -1:
                print('RCONManager: send_cmd_check_outputs: failed to find:', x.decode(), 'start:', start)
                return False
            else:
                start = find_id+len(x.decode())
        return True
    
    def get_cvar_value(self, bcvarname):
        resp=self.send_command(bcvarname)
        matches = re.search(r'is:"(.*)" default:', resp, re.DOTALL)
        if not matches:
            print('RCONManager: get_cvar_value: failed to find cvar in response:',resp)
            return ''
        return matches.group(1)

    def get_cvar_latchedvalue(self, bcvarname):
        resp=self.send_command(bcvarname)
        matches = re.search(r'latched: "(.*)"', resp)
        if not matches:
            return ''
        return matches.group(1)
    
    #instead of restarting, it sends cmd "map mapname" which shuts down and restarts nightfall.
    def reload_map(self):
        mapname = self.get_cvar_value(b'mapname')
        print('RconManager: reload_map: mapname:', mapname)
        self.send_command(b'map ' + mapname.encode())
        self.wait_for_command(b'status')
        time.sleep(10) # to ensure map is loaded
        return True
    
    def set_send_delay(self, delay):
        self.send_delay = delay