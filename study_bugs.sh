# python3 -m minishell_test
# ./minishell -c 'make fclean | cat -e'
#echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD.
./minishell -c 'echo $PWD; echo $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ..; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ../..; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ../../..; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ../../../..; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ../../../../..; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ../../../../../..; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ''; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd '' ''; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd '' '' ''; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd ' '; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd /.; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd /./; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd /././././; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd //; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ///; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd ////; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd //////////////////////////////////////////////////////; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd ' /'; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd ' / '; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd '                  /'; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd '                  /              '; pwd; echo $PWD; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd ' // '; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd //home; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd ' //home'; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
#./minishell -c 'echo $PWD; echo $OLDPWD; cd '     //home    '; pwd; echo $PWD; echo $OLDPWD| cat -e'
#echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd /; echo $PWD; echo $OLDPWD; unset PWD; cd /dev; echo $OLDPWD| cat -e'
echo =======================================tested=================================================
./minishell -c 'echo $PWD; echo $OLDPWD; cd /; echo $PWD; echo $OLDPWD; export PWD=bonjour; cd /dev; echo $OLDPWD | cat -e'
echo =======================================tested=================================================