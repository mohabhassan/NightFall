import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestStartServer():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager, request):
        print('parent:', request.node.parent)
        #print("session items:", test_items)
        test_items = request.session.items
        test_index = next((i for i, item in enumerate(test_items) if item.nodeid == request.node.nodeid), None)
        #if test_index > 0: rcon_manager.reload_map()

    #invoked by PyTest
    def test_startserver(self, game_manager, file_manager):
        pass
    def test_crashserver(self, game_manager, file_manager, rcon_manager):
        rcon_manager.reload_map()
        #keep reloading map for x retries
        #uncomment this line so that this test is retried
        #assert False
        pass

    def test_markers(self, request):
        print([[x[0], type(x[0])] for x in request.node.iter_markers_with_node()])
        pass
