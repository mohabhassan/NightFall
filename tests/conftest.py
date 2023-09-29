import pytest
from game_manager import GameManager
from file_manager import FileManager
from rcon_manager import RCONManager
from bot_manager import BotManager
import time
#pytest ./tests --game bt --gamever 2.40 --gamepath 'D:/nightfall/game/servers/BT240' --mode server --port 12203 -rA -s -x --retries 2 --timeout=120 > logbt240.txt 2>&1
#pytest ./tests --game sh --gamever 2.15 --gamepath 'D:/nightfall/game/servers/SH215' --mode server --port 12204 -rA -s -x --retries 2 --timeout=120 > logsh215.txt 2>&1
# use -k 'testname' for filtering
#takes 26 mins on my pc

def pytest_addoption(parser):
    parser.addoption("--game", action="store") #aa sh bt
    parser.addoption("--gamever", action="store") #1.11 2.15 2.30 2.40
    parser.addoption("--mode", action="store") #client server
    parser.addoption("--gamepath", action="store") #game path
    parser.addoption("--port", action="store") #game path

@pytest.fixture(scope='session')
def game(request):
    game_value = request.config.option.game
    if game_value is None:
        pytest.fail('game argument not found')
    return game_value

@pytest.fixture(scope='session')
def gamever(request):
    gamever_value = request.config.option.gamever
    if gamever_value is None:
        pytest.fail('gamever argument not found')
    return gamever_value

@pytest.fixture(scope='session')
def mode(request):
    mode_value = request.config.option.mode
    if mode_value is None:
        pytest.fail('mode argument not found')
    return mode_value

@pytest.fixture(scope='session')
def gamepath(request):
    gamepath_value = request.config.option.gamepath
    if gamepath_value is None:
        pytest.fail('gamepath argument not found')
    return gamepath_value

@pytest.fixture(scope='session')
def port(request):
    port_value = request.config.option.port
    if port_value is None:
        pytest.fail('port argument not found')
    return port_value

@pytest.fixture(scope='session')
def game_manager(game, gamever, gamepath, mode, port):
    g_man = GameManager(game, gamever, gamepath, mode, port)
    yield g_man
    print('game man stop')
    g_man.stop_game()
    assert not g_man.check_for_crashes(), 'Crash(es) occured.'


@pytest.fixture()
def file_manager(pytestconfig, request, game_manager):
    if request.node.get_closest_marker('stop_game_load_files'):
        game_manager.stop_game()
    default_testfiles = request.node.get_closest_marker('default_testfiles').args[0] if request.node.get_closest_marker('default_testfiles') else None
    file_man = FileManager(game_manager.game_path, game_manager.main_path, pytestconfig.invocation_params.dir / 'testfiles', request.node.name.split('_', maxsplit=1)[-1], default_testfiles)
    file_man.load()
    yield file_man
    file_man.unload()

@pytest.fixture(scope='session')
def rcon_manager(port):
    return RCONManager(port)

@pytest.fixture(scope='session')
def bot_manager_init(pytestconfig, port):
    return BotManager(pytestconfig.invocation_params.dir, port)

def pytest_configure(config):
    config.addinivalue_line("markers", "supported_modes")
    config.addinivalue_line("markers", "supported_game_vers")
    config.addinivalue_line("markers", "default_testfiles")
    config.addinivalue_line("markers", "stop_game_load_files")

@pytest.fixture(autouse=True)
def skip_by_gamever_and_mode(request, gamever, mode):
    if request.node.get_closest_marker('supported_game_vers') and gamever not in request.node.get_closest_marker('supported_game_vers').args:
        pytest.skip('game ver unsupported')
    if request.node.get_closest_marker('supported_modes') and mode not in request.node.get_closest_marker('supported_modes').args:
        pytest.skip('mode unsupported')

@pytest.fixture(autouse=True)
def start_game(file_manager, game_manager, rcon_manager):
    print('starting game...')
    if not game_manager.start_game():
        pytest.fail('Failed to start game')
    
    rcon_manager.wait_for_command(b'status')

@pytest.fixture()
def bot_manager(request, start_game, bot_manager_init):
    
    if request.node.get_closest_marker('stop_game_load_files'):
        bot_manager_init.stop_bot()
    bot_manager_init.ensure_connected()
    time.sleep(3)#so client cmds can be parsed
    return bot_manager_init
