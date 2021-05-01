echo $PWD; echo $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../..; pwd; echo $PWD; echo $OLDPWD

echo $PWD; echo $OLDPWD; cd ../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../../../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ../../../../../..; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ''; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '' ''; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '' '' ''; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /.; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /./; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /././././; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd //; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ///; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ////; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd //////////////////////////////////////////////////////; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' /'; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' / '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '                  /'; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '                  /              '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' // '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd //home; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd ' //home'; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd '     //home    '; pwd; echo $PWD; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /; echo $PWD; echo $OLDPWD; unset PWD; cd /dev; echo $OLDPWD
echo $PWD; echo $OLDPWD; cd /; echo $PWD; echo $OLDPWD; export PWD=bonjour; cd /dev; echo $OLDPWD

#########failed tests####################
export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=lM=m N=n O=o P=p Q=q R=r S=s T=t U=u V=v W=w X=x Y=y Z=z; echo $A$B$C$D$E$F$G$H$I$J$K$L$M$N$O$P$Q$R$S$T$U$V$W$X$Y$Z\n
echo $PWD; echo $OLDPWD; cd /; echo $PWD; echo $OLDPWD; export PWD=bonjour; cd /dev; echo $OLDPWD
export 1=a
export A='a' B='b' C='c'; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C
unset 'AH&'=nop