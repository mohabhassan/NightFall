import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestScriptMaths():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager):
        rcon_manager.reload_map()

    """Sample test"""
    #invoked by PyTest
    def test_scriptmaths(self, game_manager, file_manager, rcon_manager):
        res = ''
        while True:
            res = rcon_manager.get_cvar_value(b'test_maths_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_maths_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_maths_failed')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'