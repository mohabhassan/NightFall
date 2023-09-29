import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestStartServer():
    """Sample test"""
    #invoked by PyTest
    def test_startserver(self, game_manager, file_manager):
        pass
