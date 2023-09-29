import pytest
import time
@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestClientCMDs():
    """Sample test"""
    #invoked by PyTest
    def test_patchver(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'patchver', b'NightFall version')
    