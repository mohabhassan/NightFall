import shutil
import os

class FileManager():
    """Handle all file related operations"""
    def __init__(self, game_path, main_path, testfiles_dir, testname, default_testfiles):
        self.game_path = game_path
        self.main_path = main_path
        self.testfiles_path = testfiles_dir / testname
        self.testfiles_main_path = self.testfiles_path / 'mainfiles'
        self.gamedir_test_files = []
        self.maindir_test_files = []
        self.disabled = not os.path.exists(self.testfiles_path)

        if self.disabled:
            if default_testfiles:
                self.testfiles_path = testfiles_dir / default_testfiles
                self.testfiles_main_path = self.testfiles_path / 'mainfiles'
                self.disabled = False
            else:
                return
        self.gamedir_test_files = os.listdir(self.testfiles_path)
        self.gamedir_test_files.remove('mainfiles')
        self.maindir_test_files = os.listdir(self.testfiles_main_path)
        print('gamedir test files:', self.gamedir_test_files)
        print('maindir test files:', self.maindir_test_files)
        #pass

    #load test case files into game folder
    def load(self):
        for f in ['ipfilter.cfg','chatfilter.cfg','namefilter.cfg','protectednamefilter.cfg', 'admins.ini', 'tests', 'store.bin']:
            fpath = self.main_path / f
            if os.path.isfile(fpath):
                os.remove(fpath)
            elif os.path.isdir(fpath):
                shutil.rmtree(fpath, ignore_errors=True)
        
        if self.disabled:
            return
        shutil.copytree(self.testfiles_path, self.game_path, dirs_exist_ok=True, ignore=shutil.ignore_patterns('mainfiles'))
        shutil.copytree(self.testfiles_main_path, self.main_path, dirs_exist_ok=True)
        print('loaded test files')

    #unload test case files from game folder
    def unload(self):
        if self.disabled:
            return
        for f in self.gamedir_test_files:
            fpath = self.game_path / f
            if os.path.isfile(fpath):
                os.remove(fpath)
            elif os.path.isdir(fpath):
                shutil.rmtree(fpath, ignore_errors=True)

        for f in self.maindir_test_files:
            fpath = self.main_path / f
            if os.path.isfile(fpath):
                if os.path.splitext(fpath)[1] != '.pk3':
                    os.remove(fpath)
            elif os.path.isdir(fpath):
                shutil.rmtree(fpath, ignore_errors=True)
        
        print('unloaded test files')