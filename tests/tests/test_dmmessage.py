import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestDMMessage():
    """Sample test"""
    #invoked by PyTest
    def test_dmmessage(self, game_manager, file_manager, rcon_manager, bot_manager):
        
        #print(rcon_manager.send_command(b'status'))
        #time.sleep(1)
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testsay', b': testsay')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testsay', b': testsay')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testsay', b': testsay')
        bot_manager.disconnect()
        #time.sleep(100)
