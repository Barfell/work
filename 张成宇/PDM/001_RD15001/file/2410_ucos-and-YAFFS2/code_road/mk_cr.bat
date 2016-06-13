path = f:\WinARM\utils\bin;f:\WinARM\bin

cd yaffs2
call make -f mk_depend
call make -f mk_target
cd ..
cd lwip
call make -f mk_depend
call make -f mk_target
cd ..
cd ucos
call make -f mk_depend
call make -f mk_target
cd ..
call make -f mk_depend
call make -f mk_target