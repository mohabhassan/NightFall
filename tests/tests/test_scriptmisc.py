import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestScriptMisc():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager, request):
        test_items = request.session.items
        test_index = next((i for i, item in enumerate(test_items) if item.nodeid == request.node.nodeid), None)
        #if test_index > 0: rcon_manager.reload_map()

    def test_scriptconprintf(self, game_manager, file_manager, rcon_manager):
        while True:
            res = rcon_manager.get_cvar_value(b'test_conprintf_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        rcon_manager.send_command(b'quit')
        game_manager.wait_for_game_exit()
        mainpath = game_manager.mainpath()
        logpath = mainpath / 'qconsole.log'
        with open(logpath, 'r') as logfile:
            content = logfile.read()
            assert content.find('test_conprintf_sample_string') != -1
    
    def test_scriptgetdate(self, game_manager, file_manager, rcon_manager):
        from datetime import date
        while True:
            res = rcon_manager.get_cvar_value(b'test_getdate_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        res1 = rcon_manager.get_cvar_value(b'test_getdate_result1')
        d1 = date.today().strftime('%d.%m.%Y')
        res2 = rcon_manager.get_cvar_value(b'test_getdate_result2')
        d2 = date.today().strftime("%D")
        assert res1 == d1
        assert res2 == d2

    def test_scriptgettime(self, game_manager, file_manager, rcon_manager):
        import datetime
        while True:
            res = rcon_manager.get_cvar_value(b'test_gettime_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        res = rcon_manager.get_cvar_value(b'test_gettime_result')
        with pytest.raises(Exception) as e_info:
            datetime.strptime(res, '%H:%M:%S')

    def test_scriptgettimezone(self, game_manager, file_manager, rcon_manager):
        while True:
            res = rcon_manager.get_cvar_value(b'test_gettimezone_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        res = rcon_manager.get_cvar_value(b'test_gettimezone_result')
        tz = -time.timezone//3600
        assert int(res) == tz
        
    

    def test_scriptmiscall(self, game_manager, file_manager, rcon_manager, bot_manager):
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_misc_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_misc_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_misc_failed')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'

    #todo: test traced