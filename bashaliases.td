class BashAliases < bit hasarg, string aliasName, string aliasCommand> {
 bit hasArg = hasarg;
 string Name = aliasName;
 string Command = aliasCommand;
}


def ls_alias : BashAliases<false, "l" , "ls -ltr">;
def lsll_alias : BashAliases<false, "ll" , "ls -la">;

def cd_back1_alias:  BashAliases<false, "..1" , "cd ..">;
def cd_back2_alias:  BashAliases<false, "..2" , "cd ../..">;
def cd_back3_alias:  BashAliases<false, "..3." , "cd ../../..">;
def cd_back4_alias:  BashAliases<false, "..4" , "cd ../../../..">;
def cd_back5_alias:  BashAliases<false, "..5" , "cd ../../../..">;


def wget_alias: BashAliases<false, "wget", "wget -c">;
def mkdir_alias: BashAliases<true, "mkcd", "mkdir -p -- $1 && cd -P -- $1">;
