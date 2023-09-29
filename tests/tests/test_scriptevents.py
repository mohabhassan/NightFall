import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestScriptEvents():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager):
        rcon_manager.reload_map()

    """Sample test"""
    #invoked by PyTest
    def test_scripteventsall(self, game_manager, file_manager, rcon_manager, bot_manager):
        bot_manager.spawn()
        time.sleep(10)
        #to respawn
        #bot_manager.flush_output()
        bot_manager.check_for_output(b'')
        for i in range (3):
            bot_manager.send_command(b'+attackprimary', True)
            time.sleep(0.5)
        bot_manager.check_for_output(b'')
        time.sleep(5)
        bot_manager.check_for_output(b'')
        for i in range (3):
            bot_manager.send_command(b'-attackprimary', True)
            time.sleep(0.5)
        bot_manager.check_for_output(b'')
        print('bot running:', bot_manager.is_running())
        print('sending remiaining commands')
        bot_manager.send_command(b'keyp 29')
        time.sleep(1)
        bot_manager.send_command(b'scmd myscmd test scmd args')
        time.sleep(1)
        bot_manager.send_command(b'dmmessage 0 test dmmessage args')
        time.sleep(1)
        bot_manager.send_command(b'dmmessage -1 test dmmessage args')
        time.sleep(1)
        bot_manager.send_command(b'dmmessage 5 test dmmessage args')
        bot_manager.disconnect()
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_events_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_events_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_events_failed')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'
    
    
    def test_scripteventintermission(self, game_manager, file_manager, rcon_manager, bot_manager):
        rcon_manager.send_command(b'set fraglimit 1')
        bot_manager.spawn()
        bot2 = bot_manager.new_instance()
        bot2.spawn(b'allies')
        while True:
            mapname = rcon_manager.get_cvar_value(b'mapname')
            if not mapname or mapname != 'dm/mohdm1':
                print('invalid mapname:', mapname)
                time.sleep(5)
            else:
                break
        #intermission 0 and intermission 1 are triggered by script
        time.sleep(5)
        rcon_manager.send_command(b'restart')
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_intermissionevent_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_intermissionevent_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_intermissionevent_failed')
        #bot_manager.check_for_output(b'')
        bot_manager.disconnect()
        #bot2.check_for_output(b'')
        bot2.disconnect()
        game_manager.stop_game() #because mapchange could break other tests.
        assert passed == total, f'Score is {score}, failed tests are: {failed}'