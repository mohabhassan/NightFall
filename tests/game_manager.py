import subprocess
from pathlib import Path
import os

class GameManager():
    """Manages game instance execution/stopping"""
    game_ver_exe = {'server': {'1.11': 'MOHAA_server.exe', '2.15': 'moh_spearhead_server.exe', '2.30': 'moh_Breakthrough_server.exe', '2.40':'moh_Breakthrough_server.exe'}, 
                    'client': {'1.11': 'MOHAA.exe', '2.15': 'moh_spearhead.exe', '2.30': 'moh_breakthrough.exe', '2.40':'moh_breakthrough.exe'}}
    game_main_name = {'aa':'main', 'sh': 'mainta', 'bt': 'maintt'}
    def __init__(self, game='bt', game_ver='2.40', gamepath='D:/nightfall/game/servers/BT240', mode='client', port='12203'):
        super(GameManager, self).__init__()
        self.game = game
        self.game_ver = game_ver
        self.port = port
        self.gamespy_port = str(int(port)+97)
        self.sv_api_ports = str(int(port)+80)
        self.game_path = Path(gamepath)
        self.main_path = self.game_path / self.game_main_name[self.game]
        self.mode = mode
        self.exe_path = self.game_path / self.game_ver_exe[self.mode][self.game_ver]
        self.game_process = None

    def start_game(self):
        try:
            if self.game_running():
                return True
            SW_MINIMIZE = 6
            SW_SHOWMINNOACTIVE = 7
            if os.name != 'nt':
                info = None
            else:
                info = subprocess.STARTUPINFO()
                info.dwFlags = subprocess.STARTF_USESHOWWINDOW
                info.wShowWindow = SW_SHOWMINNOACTIVE
            print('net_port:', self.port)
            args = [self.exe_path.as_posix()]
            if self.mode == 'client':
                args += ['+set', 'dedicated', '1']
            
            args += ['+set', 'developer', '2', '+set', 'net_port', self.port, '+set', 'net_gamespy_port', self.gamespy_port, '+set', 'sv_api_ports', self.sv_api_ports,  "+exec", "server_nf.cfg"]
            # if os.name != 'nt':
            #     args = ['winedbg'] + args
            self.game_process = subprocess.Popen(args, cwd=self.game_path, startupinfo=info)
            return True
        except Exception as e:
            self.game_process = None
            print('GameManager: start_game error:', str(e))
            print('game exe path:', self.exe_path)
            return False
    
    #returns whether game is running
    def game_running(self):
        if self.game_process is None:
            return False
        else:
            return self.game_process.poll() is None
    
    #stops game process if running
    def stop_game(self):
        if self.game_running():
            self.game_process.terminate()
            self.game_process = None
    
    def wait_for_game_exit(self):
        if self.game_running():
            self.game_process.wait()
            self.game_process = None

    def game_shortname(self):
        return self.game
    
    def game_sv_api_ports(self):
        return self.sv_api_ports
    
    def mainpath(self):
        return self.main_path
    
    def check_for_crashes(self):
        return os.path.isdir(self.mainpath() / 'nightfall' / 'crashes')
        
