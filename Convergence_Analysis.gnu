set terminal  svg font "Bitstream Vera Sans, 12" linewidth 1



set output "./Convergence_Analysis/Figure/Qual_Solu.svg"
set ylabel "Qual.solution pression(%)" textcolor lt 1
set xlabel "Taille de maille(mm)" textcolor lt 2
set xrange [0.13333:0.00440] reverse
set logscale x
set logscale y
set title "Courbe de convergence de la qualité de la solution en pression" textcolor lt 3
plot "tmp" using 2:10 with linespoint title "Qua.Solu(lambda_n)", "tmp" using 2:11 with linespoint title "Qua.Solu(Sig_inter) " 
set table "./Convergence_Analysis/Data/Qual_Solu.dat"
plot "tmp" using 2:10 with linespoint title "Qua.Solu(lambda_n)", "tmp" using 2:11 with linespoint title "Qua.Solu(Sig_inter) " 
unset table
unset output
unset ylabel
unset xlabel
unset title


set output "./Convergence_Analysis/Figure/Errer_A.svg"
set ylabel "Erreur(%)" textcolor lt 1
set xlabel "Taille de maille" textcolor lt 2
set logscale x
set logscale y
set title "Courbe de convergence en erreur (Rayon de contact)" textcolor lt 3
plot "tmp" using 2:(abs(($5-$6)/$6)) with linespoint title " "
set table  "./Convergence_Analysis/Data/Errer_A.dat"
plot "tmp" using 2:(abs(($5-$6)/$6)) with linespoint title " "
unset table
unset output
unset ylabel
unset xlabel
unset title


set output "./Convergence_Analysis/Figure/Erreur_Pmax.svg"
set ylabel "Erreur(%)" textcolor lt 1
set xlabel "Taille de maille" textcolor lt 2
set logscale x
set logscale y
set title "Courbe de convergence (Pression maximale)" textcolor lt 3
plot "tmp" using 2:(abs(($7-$9)/$9)) with linespoint title "lambda_n", "tmp" using 2:(abs(($8-$9)/$9)) with linespoint title "sig22_inter"
set table "./Convergence_Analysis/Data/Erreur_Pmax.dat"
plot "tmp" using 2:(abs(($7-$9)/$9)) with linespoint title "lambda_n", "tmp" using 2:(abs(($8-$9)/$9)) with linespoint title "sig22_inter"
unset table
unset output
unset ylabel
unset xlabel
unset title



#set output "./Convergence_Analysis/Figure/Conv_A.svg"
#set ylabel "Rayon de contact(mm)" textcolor lt 1
#set xlabel "Taille de maille(mm)" textcolor lt 2
#set xrange [0.13333:0.00635] reverse
#set logscale x
#set title "Courbe de convergence (Rayon de contact)" textcolor lt 3
#plot "tmp" using 2:6 with linespoint title "Théorique","tmp" using 2:5 with linespoint title "Numérique"
#set table  "./Convergence_Analysis/Data/Conv_A.dat"
#plot "tmp" using 2:6 with linespoint title "Théorique","tmp" using 2:5 with linespoint title "Numérique"
#unset table
#unset output
#unset ylabel
#unset xlabel
#unset title


#set output "./Convergence_Analysis/Figure/Conv_Pmax.svg"
#set ylabel "Pression maximale(Mpa)" textcolor lt 1
#set xlabel "Taille de maille(mm)" textcolor lt 2
#set xrange [0.13333:0.00635] reverse
#set title "Courbe de convergence (Pression maximale)" textcolor lt 3
#plot "tmp" using 2:7 with linespoint title "lambda_n","tmp" using 2:8 with linespoint title "sig22_inter", "tmp" using 2:9 with linespoint title "Solution théorique" 
#set table "./Convergence_Analysis/Data/Conv_Pmax.dat"
#plot "tmp" using 2:7 with linespoint title "lambda_n","tmp" using 2:8 with linespoint title "sig22_inter", "tmp" using 2:9 with linespoint title "Solution théorique" 
#unset table
#unset output
#unset ylabel
#unset xlabel
#unset title


