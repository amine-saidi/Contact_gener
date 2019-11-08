#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include "Myfonction.h"
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <math.h> 
#include <sstream>
#include <iomanip>

using namespace std;
map<string,int>  mapT;


#define PI 3.14159265358979323846264338


int main (int argc, char ** argv)
{
  stringstream stream;
string line;
int Itmp;
double Dtmp;
//int tx=4;
//int ty=4;
vector<int> ID,NbrInc,NbrItr;
vector<double> Yong1,poiss1,Yong2,poiss2,Yeild2,NormalAugm,TangASF,W_Dist,Taille1,Ratio,Errmax,Delta; 
vector<string> Path,Impl,Config,Frot,Interp,statut;



fstream fichier("logfile");
getline(fichier, line); 
getline(fichier, line);
getline(fichier, line);
getline(fichier, line);
getline(fichier, line);
while(getline(fichier, line,'*')){
getline(fichier, line,'*');
istringstream iss(line);
iss>>Itmp;
ID.push_back(Itmp);

getline(fichier, line,'*');
line=removeSpaces(line);
Path.push_back(line);

getline(fichier, line,'*');
line=removeSpaces(line);
Impl.push_back(line);

getline(fichier, line,'*');
line=removeSpaces(line);
Config.push_back(line);


getline(fichier, line,'*');
line=removeSpaces(line);
Frot.push_back(line);


getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss2(line);
iss2.str(line);
iss2>>Dtmp;
Yong1.push_back(Dtmp);


getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss3(line);
iss3>>Dtmp;
poiss1.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss4(line);
iss4.str(line);
//iss>>Dtmp;
//Yong1.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss5(line);
iss5>>Dtmp;
Yong2.push_back(Dtmp);


getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss6(line);
iss6.str(line);
iss6>>Dtmp;
poiss2.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
iss.str(line);
//iss>>Dtmp;
//Yong1.push_back(Dtmp);



getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss7(line);
iss7.str(line);
iss7>>Itmp;
NbrInc.push_back(Itmp);


getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss8(line);
iss8.str(line);
iss8>>Itmp;
NbrItr.push_back(Itmp);

getline(fichier, line,'*');
line=removeSpaces(line);
Interp.push_back(line);


getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss9(line);
iss9.str(line);
iss9>>Dtmp;
NormalAugm.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss10(line);
iss10.str(line);
iss10>>Dtmp;
TangASF.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss11(line);
iss11.str(line);
iss11>>Dtmp;
W_Dist.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss12(line);
iss12.str(line);
iss12>>Dtmp;
Taille1.push_back(Dtmp);


getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss16(line);
iss16.str(line);
iss16>>Dtmp;
Ratio.push_back(Dtmp);



getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss13(line);
iss13.str(line);
iss13>>Dtmp;
Errmax.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
istringstream iss14(line);
iss14.str(line);
iss14>>Dtmp;
Delta.push_back(Dtmp);

getline(fichier, line,'*');
line=removeSpaces(line);
statut.push_back(line);



getline(fichier, line);
}

for(int k=0;k<ID.size();k++)
{
if(statut[k]!="NOK")
 {

  	int i=1,j,C1,C2,C3,nbr,tmp,nbrLign=0;
  	double x,y,z,ux,uy,uz,sig11,sig12,sig13,sig21,sig22,sig23,sig31,sig32,sig33,eto11,eto12,eto13,eto21,eto22,eto23,eto31,eto32,eto33,tmpd;
   long double R_num=0,R_th;
   double Pmax_num=0,Pmax_th;
   vector<int> CELLS_VTK[3],CELL_TYPES_VTK;
   vector<double> contact_status_VTK,lambda_n_VTK,sig[9],eto[9];
  	string str,ligne;
  	vector<double> POINTS_VTK[3],Udisp_VTK[3],POINTS_ut[3];
  	string Fill_ut=Path[k]+"/Post_Trait.vtk";
  	string Fill_VTK=Path[k]+"/PP/mort_vtk_conv_"+to_string(i)+".vtk";
  	ifstream fichier_VTK( Fill_VTK.c_str() );
  	ifstream fichier_ut( Fill_ut.c_str() );

  	
  	while(fichier_VTK )
  	{
    fichier_VTK.close(); 	  	
  	 i++;
  	 Fill_VTK=Path[k]+"/PP/mort_vtk_conv_"+to_string(i)+".vtk";
  	 fichier_VTK.open( Fill_VTK.c_str() );
  	}
  	
  	i--;
 	Fill_VTK=Path[k]+"/PP/mort_vtk_conv_"+to_string(i)+".vtk";
  	fichier_VTK.open( Fill_VTK.c_str() );
  	            
  	            
  	 while (getline(fichier_VTK, ligne))
    {
          bool test=true;
          size_t index = 0;
          nbrLign++;
          index = ligne.find("POINTS", index);
          
          if (index != string::npos) 
          {
          std::istringstream iss;
          iss.str(ligne);
          iss>>str>>nbr;
          for(j=0;j<nbr;j++)
          {
             std::istringstream iss2;
             getline(fichier_VTK, ligne);
             iss2.str(ligne);
             iss2>>x>>y>>z;
             POINTS_VTK[0].push_back(x);
             POINTS_VTK[1].push_back(y);
             POINTS_VTK[2].push_back(z);
             nbrLign++;
          }
          }
          index = 0;
          index = ligne.find("CELLS", index);
          if (index != string::npos) 
          {
  	       std::istringstream iss;
          iss.str(ligne);
          iss>>str>>nbr;
          for(j=0;j<nbr;j++)
          {
             std::istringstream iss2;
             getline(fichier_VTK, ligne);
             iss2.str(ligne);
             iss2>>C1>>C2>>C3;
             CELLS_VTK[0].push_back(C1);
             CELLS_VTK[1].push_back(C2);
             CELLS_VTK[2].push_back(C3);
             nbrLign++;

          }
          }
        
          index = 0;
          index = ligne.find("CELL_TYPES", index);
          if (index != string::npos) 
          {
  	       std::istringstream iss;
          iss.str(ligne);
          iss>>str>>nbr;
          for(j=0;j<nbr;j++)
          {
             getline(fichier_VTK, ligne);
             nbrLign++;

          }
          }
        
          
          index = 0;
          index = ligne.find("POINT_DATA", index);
          if (index != string::npos) 
          {
          std::istringstream iss;
          iss>>str>>nbr;
          getline(fichier_VTK, ligne);
          for(j=0;j<nbr;j++)
          {

             std::istringstream iss2;
             getline(fichier_VTK, ligne);
             iss2.str(ligne);          
             iss2>>ux>>uy>>uz;
             Udisp_VTK[0].push_back(ux);
             Udisp_VTK[1].push_back(uy);
             Udisp_VTK[2].push_back(uz);
             nbrLign++;
          }
          nbrLign++;
          }

          index = 0;

          index = ligne.find("contact_status", index);
          if (index != string::npos) 
          {
          getline(fichier_VTK, ligne);
          for(j=0;j<nbr;j++)
          {

             std::istringstream iss2;
             getline(fichier_VTK, ligne);
             iss2.str(ligne);          
             iss2>>tmp;
             contact_status_VTK.push_back(tmp);
             if(tmp ==-1 && test) {R_num=POINTS_VTK[0][j];test=false;}
             nbrLign++;
          }
          nbrLign++;
          }
          
          
          index = 0;
          index = ligne.find(" lambda_n", index);
          if (index != string::npos) 
          {
          getline(fichier_VTK, ligne);
          for(j=0;j<nbr;j++)
          {          
             //ligne="-1.70427e-05	-0.00249818	0.";
             std::istringstream iss2;
             getline(fichier_VTK, ligne);
             iss2.str(ligne);          
             iss2>>tmpd;
             lambda_n_VTK.push_back(tmpd);
             nbrLign++;
             Pmax_num=max(Pmax_num,abs(tmpd));
          }
          nbrLign++;
          }

  	 }
 	 
    
   
   int nbrt;
   while (getline(fichier_ut, ligne))
    {
          size_t index = 0;
          index = ligne.find("POINTS", index);
          
          if (index != string::npos) 
          {
          std::istringstream iss;
          iss.str(ligne);
          iss>>str>>nbrt;
          j=0;
          while(j<nbrt) 
          {

             std::istringstream iss2;
             getline(fichier_ut, ligne);
             iss2.str(ligne);
             while(iss2>>x)
             {
             iss2>>y>>z;
             POINTS_ut[0].push_back(x);
             POINTS_ut[1].push_back(y);
             POINTS_ut[2].push_back(z);
             j++;
             }
          }
          }
            
            
          index = 0;

          index = ligne.find("sig", index);
          
          if (index != string::npos) 
          {
          std::istringstream iss;
          iss.str(ligne);
          iss>>str>>tmp>>nbrt;
          j=0;
          while(j<nbrt) 
          {

             std::istringstream iss2;
             getline(fichier_ut, ligne);
             iss2.str(ligne);
             while(iss2>>sig11)
             {

             iss2>>sig12>>sig13>>sig21>>sig22>>sig23>>sig31>>sig32>>sig33;
             sig[0].push_back(sig11);
             sig[1].push_back(sig12);
             sig[2].push_back(sig12);
             sig[3].push_back(sig21);
             sig[4].push_back(sig22);
             sig[5].push_back(sig23);
             sig[6].push_back(sig31);
             sig[7].push_back(sig32);
             sig[8].push_back(sig33);
             j++;
             }
          }
          }
                
          index = 0;

          index = ligne.find("eto", index);
          
          if (index != string::npos) 
          {
          std::istringstream iss;
          iss.str(ligne);
          iss>>str>>tmp>>nbrt;
          j=0;
          while(j<nbrt) 
          {

             std::istringstream iss2;
             getline(fichier_ut, ligne);
             iss2.str(ligne);
             while(iss2>>eto11)
             {
             iss2>>eto12>>eto13>>eto21>>eto22>>eto23>>eto31>>eto32>>eto33;
             eto[0].push_back(eto11);
             eto[1].push_back(eto12);
             eto[2].push_back(eto12);
             eto[3].push_back(eto21);
             eto[4].push_back(eto22);
             eto[5].push_back(eto23);
             eto[6].push_back(eto31);
             eto[7].push_back(eto32);
             eto[8].push_back(eto33);
             j++;
             }
          }
          }  
         
    
  }
  


  double Rac, intg=0,Dtmp,k1,k2,Errer=0;

  creat_file(Path[k], "gnuplot_P_T_sig_inter.gnu");
  creat_file(Path[k], "readUT_P_Reaction.py");
  creat_file(Path[k], "readUT_P_T_sig_inter.py");
  creat_file(Path[k], "readUT_P_T.py");
  Add_file_in_the_end( "./Data", "gnuplot_P_T_sig_inter.gnu", Path[k], "gnuplot_P_T_sig_inter.gnu");  
  Add_file_in_the_end( "./Data", "readUT_P_T.py", Path[k], "readUT_P_T.py");
  Add_file_in_the_end( "./Data", "readUT_P_T_sig_inter.py", Path[k], "readUT_P_T_sig_inter.py");
  Add_file_in_the_end( "./Data", "readUT_P_Reaction.py", Path[k], "readUT_P_Reaction.py");
  rek_mkdir(Path[k]+"/Post_traitement/Data");
  rek_mkdir(Path[k]+"/Post_traitement/Figure");
  
  creat_file(Path[k], "gnuplot_P_T.gnu");
  Add_file_in_the_end( "./Data", "gnuplot_P_T.gnu", Path[k], "gnuplot_P_T.gnu");
  
  
  chdir(Path[k].c_str());
  system("pvbatch readUT_P_Reaction.py");
  system("pvbatch readUT_P_T_sig_inter.py");
  string Fill_RAC="reaction.tsv";
  ifstream fichier_RAC( Fill_RAC.c_str() ); 
  getline(fichier_RAC, ligne);
  while (getline(fichier_RAC, ligne))
  {
        std::istringstream iss;
        iss.str(ligne);
        iss>>Dtmp>>Dtmp>>Dtmp>>Dtmp;
        iss>>Rac;
        intg+=Rac*0.01;
  }
  intg*=2;
  fichier_RAC.close();
  chdir("../../../../.."); 
  k1=(1-poiss1[k]*poiss1[k])/(PI*Yong1[k]);
  k2=(1-poiss2[k]*poiss2[k])/(PI*Yong2[k]);
  R_th=sqrt(4*abs(intg) *(k1+k2)*20.00);
  Pmax_th=2*intg/(PI*R_th);

  string ss;
  stream.str("");
  stream << fixed << setprecision(6) << R_th;
  ss= stream.str();
  modifier_base_de_donnees( Path[k], "gnuplot_P_T_sig_inter.gnu","[A_th]   ", SForme(ss,9));
  stream.str("");
  stream << fixed << setprecision(4) << Pmax_th;
  ss= stream.str();
  modifier_base_de_donnees( Path[k], "gnuplot_P_T_sig_inter.gnu","[Pmaxth]   ", SForme(ss,11));  




    double in1 = 0,in2 =0,intgth=0;
    string Stmp=Path[k]+"/Post_Trait.data";
    ofstream flux(Stmp.c_str() ); // Flux d'ecriture
    flux<<"Px     Py   UdispX   UdispY   contact_status    lambda_n    P_th"<<endl;
    for(int i=0;i<nbr-1;i++)
    {
      flux << POINTS_VTK[0][i]<<"\t \t"<< POINTS_VTK[1][i] <<"\t \t"<<Udisp_VTK[0][i]<<"\t \t"<<Udisp_VTK[1][i]<<"\t \t"<< contact_status_VTK[i] << "\t \t"<< lambda_n_VTK[i] << "\t \t";
      if(1- POINTS_VTK[0][i]*POINTS_VTK[0][i]/(R_th*R_th)>=0) 
      {
      flux <<Pmax_th*sqrt(1- POINTS_VTK[0][i]*POINTS_VTK[0][i]/(R_th*R_th) ) << "\t \t" <<endl;
      
      if(i)
      {
      double y1=lambda_n_VTK[i-1] ,y2=lambda_n_VTK[i],a,b,a1,a2,a3;
      
      a=(y2-y1)/(Taille1[k]);
      b=y2 -a*POINTS_VTK[0][i];
      
      
      a1=a*(POINTS_VTK[0][i-1]+Taille1[k]/4)+b;
      
      in1= (Pmax_th*sqrt(1- (POINTS_VTK[0][i-1]+Taille1[k]/4)*(POINTS_VTK[0][i-1]+Taille1[k]/4)/(R_th*R_th))+Pmax_th*sqrt(1- POINTS_VTK[0][i-1]*POINTS_VTK[0][i-1]/(R_th*R_th)) ) * Taille1[k] /8;
      intgth+=in1;
      in2= (a1 + lambda_n_VTK[i-1]) *  Taille1[k]/8;
      Errer+=fabs(in1-in2);
      
      
      
      a2=a*(POINTS_VTK[0][i-1]+Taille1[k]/2)+b;
      
      in1= (Pmax_th*sqrt(1- (POINTS_VTK[0][i-1]+Taille1[k]/2)*(POINTS_VTK[0][i-1]+Taille1[k]/2)/(R_th*R_th))+Pmax_th*sqrt(1- (POINTS_VTK[0][i-1]+Taille1[k]/4)*(POINTS_VTK[0][i-1]+Taille1[k]/4)/(R_th*R_th)) ) * Taille1[k] /8;
      intgth+=in1;
      in2= (a2 + a1) *  Taille1[k]/8;
      Errer+=fabs(in1-in2);
      
      a3=a*(POINTS_VTK[0][i-1]+3*Taille1[k]/4)+b;
      
      in1= (Pmax_th*sqrt(1- (POINTS_VTK[0][i-1]+3*Taille1[k]/4)*(POINTS_VTK[0][i-1]+3*Taille1[k]/4)/(R_th*R_th))+Pmax_th*sqrt(1- (POINTS_VTK[0][i-1]+Taille1[k]/2)*(POINTS_VTK[0][i-1]+Taille1[k]/2)/(R_th*R_th)) ) * Taille1[k] /8;
      intgth+=in1;
      in2= (a3 + a2) *  Taille1[k]/8;
      Errer+=fabs(in1-in2);
      
      
      
      in1= (Pmax_th*sqrt(1- POINTS_VTK[0][i]*POINTS_VTK[0][i]/(R_th*R_th))+Pmax_th*sqrt(1- (POINTS_VTK[0][i-1]+3*Taille1[k]/4)*(POINTS_VTK[0][i-1]+3*Taille1[k]/4)/(R_th*R_th)) ) * Taille1[k] /8;
      intgth+=in1;
      in2= (lambda_n_VTK[i] + a3) *  Taille1[k]/8;
      Errer+=fabs(in1-in2);
      
      
      }
      }
      else 
      {
      flux << 0.000 <<"\t \t"<<endl;
      in2= (lambda_n_VTK[i] + lambda_n_VTK[i-1]) * Taille1[k] /2;
      Errer+=fabs(in2);
      }
    }
  Errer=Errer*100/intgth;
  flux.close();
  
  
  
  
  chdir(Path[k].c_str());
  system("pvbatch readUT_P_T.py");
  system("gnuplot gnuplot_P_T.gnu");
  system("gnuplot gnuplot_P_T_sig_inter.gnu");
  
  double sig_int=0,Dtmp2,intgth2=0,Errer2=0;
  string Fill_Sig="Sig_inter.tsv";
  ifstream Fill_sig( Fill_Sig.c_str() ); 
  getline(Fill_sig, ligne);
  int po=0;
  while (getline(Fill_sig, ligne))
  {
        std::istringstream iss;
        iss.str(ligne);
        if(po)  Dtmp2=Dtmp;
        iss>>Dtmp>>Dtmp>>Dtmp>>Dtmp;
        iss>>Dtmp;
        if(1- po*0.001*po*0.001/(R_th*R_th)>=0) 
        {
        if(po)
        {
        in1= (Pmax_th*sqrt(1- po*0.001*po*0.001/(R_th*R_th))+Pmax_th*sqrt(1- (po-1)*0.001*(po-1)*0.001/(R_th*R_th)) ) * 0.001 /2;
        intgth2+=in1;
        in2=(Dtmp+Dtmp2)*0.001/2;
        Errer2+=abs(in1-in2);
        }
        }
        else
        {
        in2=(Dtmp+Dtmp2)*0.001/2;
        Errer2+=abs(in2);
        
        }
        sig_int=max(sig_int,fabs(Dtmp));
        po++;
  }
  
  Fill_sig.close();
  chdir("../../../../..");  
  Errer2=Errer2*100/intgth2;
  
  Add_file_in_the_end("./Data","logfile_Post_T","./","logfile_Post_T"); 
  string s;

  modifier_base_de_donnees("./","logfile_Post_T","[ID] ", SForme(to_string(ID[k]),5));
  stream.str("");
  stream << fixed << setprecision(5) << Taille1[k];
  s= stream.str();
  modifier_base_de_donnees("./","logfile_Post_T","[TailM1]", SForme(s,8));
  
  
  
  stream.str("");
  stream << fixed << setprecision(5) << abs(Errer2);
  s= stream.str();
  modifier_base_de_donnees("./","logfile_Post_T","[Qua.Solu(sig_inter)]", SForme(s,21));
  stream.str("");
  stream << fixed << setprecision(5) << sig_int;
  s= stream.str();
  modifier_base_de_donnees("./","logfile_Post_T","[Sig_inte_max]", SForme(s,14));
  
  stream.str("");
  stream << fixed << setprecision(3) << Ratio[k];
  s= stream.str(); 
  modifier_base_de_donnees("./","logfile_Post_T","[Rat] ", SForme(s,6));

      
  stream.str("");
  stream << fixed << setprecision(6) << R_num;
  s= stream.str(); 
  modifier_base_de_donnees("./","logfile_Post_T","[R_num]  ", SForme(s,9));
  
  stream.str("");
  stream << fixed << setprecision(4) << Pmax_num;
  s= stream.str(); 
  modifier_base_de_donnees("./","logfile_Post_T","[Pmax_num]", SForme(s,10));
  
  stream.str("");
  stream << fixed << setprecision(4) << NbrItr[k];
  s= stream.str(); 
  modifier_base_de_donnees("./","logfile_Post_T","[nbrIteration]", SForme(s,14));
  
  stream.str("");
  stream << fixed << setprecision(6) << R_th;
  s= stream.str(); 
  modifier_base_de_donnees("./","logfile_Post_T","[R_th]   ", SForme(s,9));
  stream.str("");
  stream << fixed << setprecision(4) << abs(Pmax_th);
  s= stream.str(); 
  modifier_base_de_donnees("./","logfile_Post_T","[Pmax_th]   ", SForme(s,12));
  stream.str(""); 
  stream << fixed << setprecision(5) << abs(Errer);
  s= stream.str(); 
  modifier_base_de_donnees("./","logfile_Post_T","[Qua.Solu(P)]   ", SForme(s,16));
  stream.str(""); 
   
  
  }
  

  }
  



return EXIT_SUCCESS;
}

