import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestScriptPlayerMisc():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager, bot_manager):
        rcon_manager.reload_map()

    def test_scriptplayermiscall(self, game_manager, file_manager, rcon_manager, bot_manager):
        bot_manager.spawn()
        
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_playermisc_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_playermisc_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_playermisc_failed')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'

    def test_scriptplayersecfireheld(self, game_manager, file_manager, rcon_manager, bot_manager):
        bot_manager.spawn()
        time.sleep(5)
        bot_manager.send_command(b'+attacksecondary')
        time.sleep(1)
        rcon_manager.send_command(b'set test_playersecfireheld_botstatus secfireheld')
        time.sleep(10)
        bot_manager.send_command(b'-attacksecondary')
        time.sleep(1)
        rcon_manager.send_command(b'set test_playersecfireheld_botstatus nosecfireheld')
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_playersecfireheld_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_playersecfireheld_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_playersecfireheld_failed')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'

        
    def test_scriptplayerisadmin(self, game_manager, file_manager, rcon_manager, bot_manager):
        #bot_manager.spawn()
        time.sleep(5)
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        time.sleep(1)
        rcon_manager.send_command(b'set test_playerisadmin_botstatus admin')
        time.sleep(10)
        assert bot_manager.send_cmd_await_output(b'ad_logout', b'Admin System> You have logged out as admin')
        time.sleep(1)
        rcon_manager.send_command(b'set test_playerisadmin_botstatus noadmin')
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_playerisadmin_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_playerisadmin_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_playerisadmin_failed')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'