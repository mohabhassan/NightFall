import configparser
config = configparser.ConfigParser()
config.read('./config.ini')

class GameLoader():
    """Loads AA/SH/BT Server/Client"""
    def __init__(self, game='bt2.40'): #aa, sh, bt2.30, bt2.40
        super(GameLoader, self).__init__()
        self.game = game[:2]
        self.gamever = game[2:]

    def load_game(self):
        pass


    

