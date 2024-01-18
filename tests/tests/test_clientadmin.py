import pytest
import time
#takes approx 8 mins on my pc
@pytest.mark.supported_modes('server', 'client')
@pytest.mark.supported_game_vers('1.11', '2.15', '2.30', '2.40')
@pytest.mark.default_testfiles('admins_ini')
@pytest.mark.stop_game_load_files()
class TestClientAdmin():
    """Sample test"""
    #invoked by PyTest
    def test_ad_login(self, game_manager, file_manager, rcon_manager, bot_manager):
        rcon_manager.reload_map()
        #print(rcon_manager.send_command(b'status'))
        #time.sleep(1)
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
    
    def test_ad_logout(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_logout', b'Admin System> You have logged out as admin')
    
    def test_ad_say(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_say wewewe', b'console: wewewe')

    def test_ad_kick(self, game_manager, file_manager, rcon_manager, bot_manager):
        bots = bot_manager.new_muliple_instances(1)
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_kick mohpc_test1', b'mohpc_test1 was kicked')

    def test_ad_kickr(self, game_manager, file_manager, rcon_manager, bot_manager):
        bots = bot_manager.new_muliple_instances(1)
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_kickr mohpc_test1 myreason', b'mohpc_test1 was kicked for myreason')

    def test_ad_clientkick(self, game_manager, file_manager, rcon_manager, bot_manager):
        bots = bot_manager.new_muliple_instances(1)
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_clientkick 2', b'mohpc_test1 was kicked')

    def test_ad_clientkickr(self, game_manager, file_manager, rcon_manager, bot_manager):
        bots = bot_manager.new_muliple_instances(1)
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_clientkickr 2 myreason', b'mohpc_test1 was kicked for myreason')

    def test_ad_banip(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banip 127.0.0.1', b'IP 127.0.0.1 banned successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\nBanned IP.')
        rcon_manager.send_command(b'unbanip 127.0.0.1')
        bot.disconnect()

    def test_ad_banipr(self, game_manager, file_manager, rcon_manager, bot_manager):
        #todo: check for others are banned message
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banipr 127.0.0.1 mybanipr', b'IP 127.0.0.1 banned successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\nBanned IP.')
        rcon_manager.send_command(b'unbanip 127.0.0.1')
        bot.disconnect()

    def test_ad_banid(self, game_manager, file_manager, rcon_manager, bot_manager):
        bot = bot_manager.new_instance()
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banid 2', b'mohpc_test1 was banned')
        bot.disconnect()
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\nBanned IP.')
        bot.disconnect()
        rcon_manager.send_command(b'unbanip 127.0.0.1')

    def test_ad_banidr(self, game_manager, file_manager, rcon_manager, bot_manager):
        bot = bot_manager.new_instance()
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banidr 2 myreason', b'mohpc_test1 was banned for myreason')
        bot.disconnect()
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\nBanned IP.')
        rcon_manager.send_command(b'unbanip 127.0.0.1')
        bot.disconnect()

    def test_ad_unbanip(self, game_manager, file_manager, rcon_manager, bot_manager):
        #todo: check for others are banned message
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banip 127.0.0.1', b'IP 127.0.0.1 banned successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\nBanned IP.')
        assert bot_manager.send_cmd_await_output(b'ad_unbanip 127.0.0.1', b'IP removed from ban filter')
        assert bot_manager.send_cmd_await_output(b'ad_unbanip 127.0.0.1', b'IP does not exist in ban filter')
        bot.disconnect()

    @pytest.mark.stop_game_load_files()
    def test_ad_listips1(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listips 1', [b'===PAGE START===', b'127.1.1.1', b'1.1.1.1', b'===PAGE END===', b'Showed 2 IPs from 1 to 2 out of 2 banned IPs'])
        assert bot_manager.send_cmd_await_output(b'ad_listips 2', b'Page Empty')
    
    @pytest.mark.stop_game_load_files()
    def test_ad_listips2(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listips 56', [b'75.249.238.34', b'251.26.248.39', b'45.235.228.148', b'205.97.27.46', b'102.134.229.79', b'53.104.189.166', b'223.154.97.34', b'127.231.252.49', b'3.33.11.36', b'101.45.202.14', b'252.30.217.95', b'159.149.7.130', b'177.83.231.81', b'218.131.193.176', b'191.206.117.94', b'95.64.25.12', b'142.75.32.224', b'216.253.49.66', b'122.182.172.44', b'185.200.72.87', b'19.47.212.132', b'40.19.0.114', b'251.54.75.143', b'174.8.65.80', b'231.193.54.107', b'14.219.52.69', b'91.90.38.52', b'109.129.104.173', b'33.112.58.52', b'164.176.39.205', b'152.187.249.164', b'126.39.79.44', b'235.53.224.153', b'195.166.50.85', b'232.79.179.148', b'70.57.198.76', b'55.158.29.70', b'154.112.58.166', b'6.210.217.169', b'227.83.247.20', b'82.221.101.193', b'86.205.223.198', b'115.253.35.164', b'191.147.184.94', b'4.15.113.113', b'46.3.88.183', b'232.54.55.210', b'202.29.230.50', b'81.29.144.220', b'35.253.86.35', b'127.102.189.59', b'236.24.237.158', b'42.131.46.112', b'133.235.228.152', b'204.174.200.236', b'96.151.160.197', b'37.88.178.52', b'55.45.5.45', b'240.195.194.34', b'244.128.150.159', b'41.233.131.72', b'34.167.45.153', b'86.3.107.21', b'188.37.163.77', b'196.245.148.240', b'165.25.48.34', b'151.217.71.233', b'228.197.224.211', b'153.96.54.52', b'46.187.93.72', b'207.231.35.36', b'76.220.107.171', b'134.46.96.222', b'119.21.97.154', b'58.41.182.201', b'33.167.60.126', b'167.16.139.232', b'183.154.93.35', b'45.225.142.220', b'210.111.142.58', b'143.52.5.82', b'218.165.122.171', b'45.8.138.181', b'207.105.204.31', b'34.10.87.134', b'83.118.132.206', b'217.120.59.155', b'244.238.167.103', b'152.109.90.222', b'152.73.184.58', b'222.196.57.72', b'43.128.5.50', b'41.169.18.175', b'241.97.145.200', b'34.118.188.163', b'100.5.154.183', b'60.24.86.233', b'122.162.100.7', b'182.80.135.88', b'241.90.189.104', b'Showed 100 IPs from 5501 to 5600 out of 5632 banned IPs'])
        assert bot_manager.send_cmd_await_outputs(b'ad_listips 57', [b'218.231.29.111', b'37.21.146.38', b'39.155.34.136', b'252.25.45.116', b'74.251.145.229', b'175.8.92.71', b'244.21.214.205', b'38.111.212.54', b'65.17.81.154', b'122.128.149.175', b'188.234.93.190', b'113.34.134.20', b'234.18.164.163', b'227.161.94.50', b'100.212.118.9', b'63.2.90.160', b'9.200.162.51', b'1.161.231.101', b'3.250.166.184', b'34.125.218.65', b'92.25.174.230', b'84.31.98.13', b'40.233.126.134', b'232.240.168.193', b'231.4.71.40', b'154.78.190.226', b'94.102.99.169', b'153.6.2.139', b'140.196.117.175', b'51.236.10.109', b'2.2.2.2', b'2.*.2.2', b'Showed 32 IPs from 5601 to 5632 out of 5632 banned IPs'])
        assert bot_manager.send_cmd_await_output(b'ad_listips 58', b'Page Empty')
    
    def test_ad_banname1(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banname mohpc_test1', b'Name mohpc_test1 banned successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\ndisallowed name or disallowed word in name.')
        rcon_manager.send_command(b'unbanname mohpc_test1')
        bot.disconnect()
    
    def test_ad_banname2(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banname test 1', b'Name test ~any banned successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\ndisallowed name or disallowed word in name.')
        rcon_manager.send_command(b'unbanname test')
        bot.disconnect()
    
    def test_ad_unbanname(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_banname mohpc_test1', b'Name mohpc_test1 banned successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\ndisallowed name or disallowed word in name.')
        assert bot_manager.send_cmd_await_output(b'ad_unbanname mohpc_test1', b'Name removed from ban filter')
        assert bot_manager.send_cmd_await_output(b'ad_unbanname mohpc_test1', b'Name does not exist in ban filter')
        bot.disconnect()

    @pytest.mark.stop_game_load_files()
    def test_ad_listnames1(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listnames 1', [b'===PAGE START===', b'test', b'wewewe', b'xoxox ~any', b'===PAGE END===', b'Showed 3 Names from 1 to 3 out of 3 banned Names'])
        assert bot_manager.send_cmd_await_output(b'ad_listnames 2', b'Page Empty')

    @pytest.mark.stop_game_load_files()
    def test_ad_listnames2(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listnames 10', [b'delong', b'welker', b'christiansen', b'salerno', b'aaron', b'ocampo', b'stubblefield', b'christie', b'ibrahim', b'scruggs', b'damico', b'calloway', b'reece', b'sparks', b'xu', b'james', b'simon', b'madrigal', b'prather', b'franco', b'keating', b'carlin', b'bunch', b'cohen', b'pritchard', b'shaver', b'redmond', b'barger', b'key', b'post', b'gallo', b'schott', b'sigler', b'beall', b'hoskins', b'tomlinson', b'spurlock', b'crain', b'self', b'baca', b'chaffin', b'low', b'womack', b'merrell', b'chong', b'mckee', b'casteel', b'gross', b'belcher', b'muhammad', b'elmore', b'conti', b'fries', b'reid', b'boyer', b'kunkel', b'hyatt', b'freed', b'withrow', b'wertz', b'baltazar', b'decker', b'peyton', b'mccoy', b'ogden', b'butcher', b'duarte', b'bourgeois', b'siegel', b'dobbins', b'hebert', b'dudley', b'ngo', b'stamper', b'peek', b'ledford', b'roland', b'ezell', b'garber', b'bradley', b'milner', b'harris', b'sanders', b'baird', b'sommers', b'rawls', b'cross', b'keys', b'hodgson', b'young', b'bird', b'crespo', b'brady', b'rupp', b'cardwell', b'gibbons', b'mccarter', b'trammell', b'sample', b'redd', b'Showed 100 Names from 901 to 1000 out of 1025 banned Names'])
        assert bot_manager.send_cmd_await_outputs(b'ad_listnames 11', [b'beckwith', b'trahan', b'schmidt', b'cronin', b'aguilera', b'huff', b'thurston', b'hendrix', b'fernandez', b'owen', b'noriega', b'boles', b'timmons', b'adler', b'curtis', b'mares', b'pitt', b'sylvester', b'knott', b'kelso', b'welch', b'fortner', b'alvarado', b'chisholm', b'kincaid', b'Showed 25 Names from 1001 to 1025 out of 1025 banned Names'])
        assert bot_manager.send_cmd_await_output(b'ad_listnames 12', b'Page Empty')
    
    def test_ad_protname1(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_protname mohpc_test1 tp', b'Name mohpc_test1 protected successfully')
        assert bot_manager.send_cmd_await_output(b'ad_protname mohpc_test1 tp', b'Name mohpc_test1 already protected')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\nusing protected name w/o permission')
        rcon_manager.send_command(b'unprotname mohpc_test1')
        bot.disconnect()

    def test_ad_protname2(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_protname mohpc_test1 tp', b'Name mohpc_test1 protected successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot('-s', 'tpasfadsf')
        assert bot.wait_for_output(b'Server rejected connection:\\nusing protected name w/o permission')
        bot.disconnect()
        bot = bot_manager.new_instance(False)
        bot.start_bot('-s', 'tp')
        bot.wait_till_connected()
        rcon_manager.send_command(b'unprotname mohpc_test1')
        bot.disconnect()
    
    def test_ad_unprotname(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_protname mohpc_test1 tp', b'Name mohpc_test1 protected successfully')
        bot = bot_manager.new_instance(False)
        bot.start_bot()
        assert bot.wait_for_output(b'Server rejected connection:\\nusing protected name w/o permission')
        assert bot_manager.send_cmd_await_output(b'ad_unprotname mohpc_test1', b'Name removed from protected filter')
        assert bot_manager.send_cmd_await_output(b'ad_unprotname mohpc_test1', b'Name does not exist in protected filter')
        bot.disconnect()
        bot = bot_manager.new_instance()
        bot.disconnect()
    
    """ad_listprotnames 1
    [09:03:46] (test_net) @_trace => server print (7): "===PAGE START===
    name=brayden password=weatherford
    name=calvin password=hendrickson
    name=jackie password=ocampo
    ===PAGE END===
    Showed 3 protected names from 1 to 3 out of 3 protected Names"""
    """
    name=jaylon password=ceballos
    ===PAGE END===
    Showed 100 protected names from 1 to 100 out of 845 protected Names
    """
    
    @pytest.mark.stop_game_load_files()
    def test_ad_listprotnames1(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listprotnames 1', [b'===PAGE START===', b'name=brayden password=weatherford', b'name=calvin password=hendrickson', b'name=jackie password=ocampo', b'===PAGE END===', b'Showed 3 protected names from 1 to 3 out of 3 protected Names'])
        assert bot_manager.send_cmd_await_output(b'ad_listprotnames 2', b'Page Empty')

    @pytest.mark.stop_game_load_files()
    def test_ad_listprotnames2(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listprotnames 1', [b'name=jaylon password=ceballos', b'===PAGE END===', b'Showed 100 protected names from 1 to 100 out of 845 protected Names'])
        assert bot_manager.send_cmd_await_output(b'ad_listprotnames 10', b'Page Empty')

    
    def test_ad_chatfilteradd1(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testword', b': testword')
        assert bot_manager.send_cmd_await_output(b'ad_chatfilteradd testword', b'Word testword banned from chat successfully')
        assert bot_manager.send_cmd_await_outputs(b'dmmessage 0 testword', [b'Dissallowed word in chat', b'You have 2 more warning(s) remiaining'])
        assert bot_manager.send_cmd_await_outputs(b'dmmessage 0 testword', [b'Dissallowed word in chat', b'You have 1 more warning(s) remiaining'])
        assert bot_manager.send_cmd_await_outputs(b'dmmessage 0 testword', [b'Kicked from server for', b'Dissallowed word in chat', b'Maximum number of 3 warning(s) reached'])

    @pytest.mark.stop_game_load_files()
    def test_ad_chatfilteradd2(self, game_manager, file_manager, rcon_manager, bot_manager):
        rcon_manager.send_command(b'set g_badchatlimit 1')
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testword', b': testword')
        assert bot_manager.send_cmd_await_output(b'ad_chatfilteradd testword', b'Word testword banned from chat successfully')
        assert bot_manager.send_cmd_await_outputs(b'dmmessage 0 testword', [b'Kicked from server for', b'Dissallowed word in chat', b'Maximum number of 1 warning(s) reached'])
        
    @pytest.mark.stop_game_load_files()
    def test_ad_chatfilterremove(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testword', b': testword')
        assert bot_manager.send_cmd_await_output(b'ad_chatfilteradd testword', b'Word testword banned from chat successfully')
        assert bot_manager.send_cmd_await_outputs(b'dmmessage 0 testword', [b'Dissallowed word in chat', b'You have 2 more warning(s) remiaining'])
        assert bot_manager.send_cmd_await_output(b'ad_chatfilterremove testword', b'Word removed from chat filter')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testword', b': testword')

    @pytest.mark.stop_game_load_files()
    def test_ad_listchatfilter1(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listchatfilter 1', [b'===PAGE START===', b'test', b'wewewe', b'xoxox', b'===PAGE END===', b'Showed 3 words from 1 to 3 out of 3 banned words'])
        assert bot_manager.send_cmd_await_output(b'ad_listchatfilter 2', b'Page Empty')

    @pytest.mark.stop_game_load_files()
    def test_ad_listchatfilter2(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listchatfilter 10', [b'delong', b'welker', b'christiansen', b'salerno', b'aaron', b'ocampo', b'stubblefield', b'christie', b'ibrahim', b'scruggs', b'damico', b'calloway', b'reece', b'sparks', b'xu', b'james', b'simon', b'madrigal', b'prather', b'franco', b'keating', b'carlin', b'bunch', b'cohen', b'pritchard', b'shaver', b'redmond', b'barger', b'key', b'post', b'gallo', b'schott', b'sigler', b'beall', b'hoskins', b'tomlinson', b'spurlock', b'crain', b'self', b'baca', b'chaffin', b'low', b'womack', b'merrell', b'chong', b'mckee', b'casteel', b'gross', b'belcher', b'muhammad', b'elmore', b'conti', b'fries', b'reid', b'boyer', b'kunkel', b'hyatt', b'freed', b'withrow', b'wertz', b'baltazar', b'decker', b'peyton', b'mccoy', b'ogden', b'butcher', b'duarte', b'bourgeois', b'siegel', b'dobbins', b'hebert', b'dudley', b'ngo', b'stamper', b'peek', b'ledford', b'roland', b'ezell', b'garber', b'bradley', b'milner', b'harris', b'sanders', b'baird', b'sommers', b'rawls', b'cross', b'keys', b'hodgson', b'young', b'bird', b'crespo', b'brady', b'rupp', b'cardwell', b'gibbons', b'mccarter', b'trammell', b'sample', b'redd', b'Showed 100 words from 901 to 1000 out of 1025 banned words'])
        assert bot_manager.send_cmd_await_outputs(b'ad_listchatfilter 11', [b'beckwith', b'trahan', b'schmidt', b'cronin', b'aguilera', b'huff', b'thurston', b'hendrix', b'fernandez', b'owen', b'noriega', b'boles', b'timmons', b'adler', b'curtis', b'mares', b'pitt', b'sylvester', b'knott', b'kelso', b'welch', b'fortner', b'alvarado', b'chisholm', b'kincaid', b'Showed 25 words from 1001 to 1025 out of 1025 banned words'])
        assert bot_manager.send_cmd_await_output(b'ad_listchatfilter 12', b'Page Empty')

    def test_ad_dischat(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testword', b': testword')
        assert bot_manager.send_cmd_await_output(b'ad_dischat 1', b'Disabled chat for client 1')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testword', b'Chat disabled for you')
        assert bot_manager.send_cmd_await_output(b'ad_dischat 1', b'Enabled chat for client 1')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 testword', b': testword')
    """
    dmmessage 0 *11
[23:38:44] (test_net) @_trace => server print (2): "(team) mohpc_test0: Good job team!"
dmmessage 0 *11
[23:39:08] (test_net) @_trace => server hud print: "Taunts disabled for you.
Disabled taunts for client 1
Enabled taunts for client 1
    """
    
    def test_ad_distaunt(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        bot_manager.spawn()
        # bt: mohpc_test0: Good job team!
        # sh: mohpc_test0: Good job team!
        # aa: mohpc_test0: Squad, move in!
        expected_output = b'mohpc_test0: ' + b'Squad, move in!' if game_manager.game_shortname() == 'aa' else b'Good job team!'
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 *11', expected_output)
        assert bot_manager.send_cmd_await_output(b'ad_distaunt 1', b'Disabled taunts for client 1')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 *11', b'Taunts disabled for you')
        assert bot_manager.send_cmd_await_output(b'ad_distaunt 1', b'Enabled taunts for client 1')
        assert bot_manager.send_cmd_await_output(b'dmmessage 0 *11', expected_output)
    
    def test_ad_say(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_say test say', b'console: test say')
    
    def test_ad_sayp(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        bot = bot_manager.new_instance()
        bot.flush_output()
        assert bot_manager.send_cmd_await_output(b'ad_sayp 1 test say', b'console: test say')
        #there's no easy way to check if bot doesn't have output
        #assert bot.check_for_output(b'', True)
        #print('bot output exists:', bot.output_exists())
        bot_manager.flush_output()
        bot.flush_output()
        bot_manager.send_command(b'ad_sayp 2 test say')

        assert bot.wait_for_output(b'console: test say')
        bot.disconnect()
    
    @pytest.mark.stop_game_load_files()
    def test_ad_listadmins(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_outputs(b'ad_listadmins', [b'Name | Rights', b'mohpc_test0 | 16383'])

    def test_ad_map(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_map dm/mohdm2', b'mohpc_test0 has entered the battle')
        assert rcon_manager.get_cvar_value(b'mapname') == 'dm/mohdm2'
    
    def test_ad_restart(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_restart', b'mohpc_test0 has entered the battle')
    
    def test_ad_fraglimit(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        fraglimit = rcon_manager.get_cvar_value(b'fraglimit')
        assert fraglimit != ''
        fraglimit = int(fraglimit)
        fraglimit = max(fraglimit+1, 7)
        bot_manager.send_command(b'ad_fraglimit ' + str(fraglimit).encode())
        time.sleep(1) # so cvar change can be executed
        assert rcon_manager.get_cvar_value(b'fraglimit') == str(fraglimit)

    def test_ad_timelimit(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        timelimit = rcon_manager.get_cvar_value(b'timelimit')
        assert timelimit != ''
        timelimit = int(timelimit)
        timelimit = max(timelimit+1, 7)
        bot_manager.send_command(b'ad_timelimit ' + str(timelimit).encode())
        time.sleep(5) # so cvar change can be executed
        assert rcon_manager.get_cvar_value(b'timelimit') == str(timelimit)

    def test_ad_gametype(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        bot_manager.send_command(b'ad_gametype 1')
        time.sleep(1) # so cvar change can be executed
        assert rcon_manager.get_cvar_latchedvalue(b'g_gametype') == '1'
    
    def test_ad_rcon(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_rcon say test rcon say', b'console: test rcon say')
    
    def test_ad_status(self, game_manager, file_manager, rcon_manager, bot_manager):
        assert bot_manager.send_cmd_await_output(b'ad_login test test', b'Admin System> You have been authed as admin')
        assert bot_manager.send_cmd_await_output(b'ad_status', b'Num | Ping | Name | IP | Port | Rate')
    
    #TODO: test permission system