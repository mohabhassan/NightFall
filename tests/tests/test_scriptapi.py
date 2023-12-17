import pytest
import time
import requests
import json

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestScriptAPI():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager, request):
        test_items = request.session.items
        test_index = next((i for i, item in enumerate(test_items) if item.nodeid == request.node.nodeid), None)
        #if test_index > 0: rcon_manager.reload_map()


    def test_scriptapiclient(self, game_manager, file_manager, rcon_manager):
        while True:
            res = rcon_manager.get_cvar_value(b'test_apiclient_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_apiclient_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_apiclient_failed')
        failed = failed.replace('\n','\\n')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'
        
    def test_scriptapiserver(self, game_manager, file_manager, rcon_manager):
        query_params = {'key1': 'value1', 'key2': 'value2'}
        resp = requests.get('http://localhost:8080/', params=query_params)
        print('get response text: ', resp.text)
        assert resp.text == '{"message":{"content":{"0":{"content":"sdgfdsg","type":"string"},"1":{"content":"etaseg","type":"string"},"2":{"content":"wewewewewew","type":"string"}},"type":"array_object"},"status":"success"}'
        body = json.dumps({'key1': 'value1', 'key2': 'value2'})
        print('post request body: ', body)
        resp = requests.post('http://localhost:8080/posttest', data=body)
        print('post response text: ', resp.text)
        assert resp.text == '{"message":{"content":{"0":{"content":"sdgfdsg","type":"string"},"1":{"content":"etaseg","type":"string"},"2":{"content":"wewewewewew","type":"string"}},"type":"array_object"},"status":"success"}'
        resp = requests.get('http://localhost:8080/', params=query_params)
        assert resp.status_code == 404
        resp = requests.post('http://localhost:8080/posttest')
        assert resp.status_code == 404

        while True:
            res = rcon_manager.get_cvar_value(b'test_apiserver_status')
            if not res or res == 'running':
                time.sleep(5)
            else:
                break
        score = rcon_manager.get_cvar_value(b'test_apiserver_score')
        passed, total = score.split('/')
        failed = rcon_manager.get_cvar_value(b'test_apiserver_failed')
        failed = failed.replace('\n','\\n')
        assert passed == total, f'Score is {score}, failed tests are: {failed}'
