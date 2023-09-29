import pytest
import time

@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.stop_game_load_files()
class TestScriptIHudDraw():
    @pytest.fixture(autouse=True)
    def reload_map(self, rcon_manager):
        rcon_manager.reload_map()

    """Sample test"""
    #invoked by PyTest
    def test_scriptihuddraw(self, game_manager, file_manager, rcon_manager, bot_manager):
        bot_output = [
            b'huddraw_align : 32 l t',
            b'huddraw_font : 32 courier-20',
            b'huddraw_rect : 32 20 400 600 64',
            b'huddraw_color : 32 0.00 0.00 1.00',
            b'huddraw_alpha : 32 1.00',
            b'huddraw_shader : 32 "textures/common/black"',
            b'huddraw_virtualsize : 32 1',

            b'huddraw_align : 33 l t',
            b'huddraw_font : 33 courier-20',
            b'huddraw_rect : 33 20 100 600 64',
            b'huddraw_color : 33 1.00 0.00 0.00',
            b'huddraw_alpha : 33 1.00',
            b'huddraw_shader : 33 "textures/common/black"',
            b'huddraw_virtualsize : 33 1',

            b'huddraw_align : 34 c t',
            b'huddraw_font : 34 courier-20',
            b'huddraw_rect : 34 0 125 550 64',
            b'huddraw_color : 34 1.00 1.00 1.00',
            b'huddraw_alpha : 34 1.00',
            b'huddraw_virtualsize : 34 1',
            b'huddraw_string : 34 PLEASE DO NOT FIRE.YOU ARE BEING CHECKED BY ADMIN.',

            b'huddraw_align : 35 c t',
            b'huddraw_font : 35 courier-20',
            b'huddraw_rect : 35 0 432 420 64',
            b'huddraw_color : 35 1.00 1.00 1.00',
            b'huddraw_alpha : 35 1.00',
            b'huddraw_virtualsize : 35 1',
            b'huddraw_string : 35 MATDRB4 NAR.EL ADMIN BY3ML CHECK 3LEEK.',

            b'huddraw_align : 36 l t',
            b'huddraw_font : 36 courier-20',
            b'huddraw_rect : 36 220 240 600 64',
            b'huddraw_color : 36 0.00 1.00 0.00',
            b'huddraw_alpha : 36 1.00',
            b'huddraw_shader : 36 "textures/common/caulk"',
            b'huddraw_virtualsize : 36 1'
        ]
        for x in bot_output:
            assert bot_manager.wait_for_output(x)