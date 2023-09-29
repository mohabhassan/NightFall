import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestScriptFileSystem():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager):
        rcon_manager.reload_map()

    def test_scriptfilesystem(self, game_manager, file_manager, rcon_manager):
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_filesystem_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_filesystem_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_filesystem_failed')
        failed = failed.replace('\n','\\n')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'

    #todo: test traced