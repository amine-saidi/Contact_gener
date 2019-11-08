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

extern    map<string,int>  mapT;




void cb_activate (GtkEntry * p_entry, gpointer p_data) 
{ 
   GtkWidget * p_widget = (GtkWidget*)p_data; 
  
   g_return_if_fail (GTK_IS_WIDGET (p_entry)); 
  
   gtk_widget_grab_focus (p_widget); 
} 

string PathFSrc = "./Data";

string OutputPath = "./Output";
ThisModel T_Model;
Model This_Model;
Maillage This_Maillage;
Comportement This_Comportement;

string SForme(string str,int nbr)
{
 while(str.size()!=(unsigned)nbr)
 {
  str =str+" ";
  
 }
 return str;
} 

template <typename T>

vector<T> extract(string s)
{
  s = removeSpaces(s);
  vector<T> data;
  std::string line, temp;
  if (s[0] == '{')
  {
    temp = s.substr(1, s.size() - 2);
    istringstream input(temp);
    while (std::getline(input, line, ';'))
    {
      std::istringstream iss(line);
      T d;
      iss >> d;
      data.push_back(d);
    }
  }
  else if (s[0] == '[')
  {
    temp = s.substr(1, s.size() - 2);
    T d1, d2, d3;
    istringstream input(temp);
    getline(input, line, ':');
    std::istringstream iss(line);
    iss.str(line);
    iss >> d1;
    getline(input, line, ':');
    cout << "s=[" << line << "]" << endl;
    std::istringstream iss2(line);
    iss2 >> d2;
    getline(input, line);
    std::istringstream iss3(line);
    iss3 >> d3;
    cout << d1 << " " << d2 << " " << d3 << endl;
    while (d1 <= d2)
    {
      data.push_back(d1);
      d1 += d3;
    }
  }
  else
  {
    temp = s;
    istringstream input(temp);
    while (std::getline(input, line, ';'))
    {
      std::istringstream iss(line);
      T d;
      iss >> d;
      data.push_back(d);
    }
  }
  return data;
}

void createMesh(string Path,double R,int n,int CutsX,int CutsY ,int config,int IN , double ratio,int I)
{
   if(I)
   {
   double dist=2;
   string s,todel;
	stringstream stream;
	long double theta[2*n+2],p2y[n+2],p3x[n+2],p0y[n+2],p1y[n+2],p2x[n+2],p5y[n+2],p6y[n+2];
   int T_CutsX,T_CutsY;
	creat_file(Path,"R_Sph_Bott.mast");
	Add_file_in_the_end(PathFSrc+"/Maillage" ,"Sph_Bot.mast",Path,"R_Sph_Bott.mast");
   if(config==0)
   {
    if(IN==0)
    {
    modifier_base_de_donnees(Path,"R_Sph_Bott.mast","c2d4","cax4");
    }
    else
    {
    modifier_base_de_donnees(Path,"R_Sph_Bott.mast","c2d4","cax8");
    modifier_base_de_donnees(Path,"R_Sph_Bott.mast","*order 1","*order 2");

    }

   }
   else
   {
   if(IN==1)
    {
     modifier_base_de_donnees(Path,"R_Sph_Bott.mast","c2d4","c2d8");
     modifier_base_de_donnees(Path,"R_Sph_Bott.mast","c2d3","c2d6");
     modifier_base_de_donnees(Path,"R_Sph_Bott.mast","*order 1","*order 2");
    }
    
    
   }

   
   p0y[0]=dist;p3x[0]=dist;
   stream << fixed << setprecision(15) << p0y[0];
	s= stream.str(); 
	modifier_base_de_donnees(Path,"R_Sph_Bott.mast","[p0.y]",s);
	stream.str("");

	stream << fixed << setprecision(15) << p3x[0];
	s= stream.str();
	modifier_base_de_donnees(Path,"R_Sph_Bott.mast","[p3.x]",s);
	stream.str("");

	stream << fixed << setprecision(15) << R;
	s= stream.str();
	modifier_base_de_donnees(Path,"R_Sph_Bott.mast","[R]",s);
	stream.str("");

	p2y[0]=R-sqrt(R*R-p3x[0]*p3x[0]);
	theta[0]=M_PI*1.5+asin(p3x[0]/R);
	stream << fixed << setprecision(15) << p2y[0];
	s= stream.str(); 
	modifier_base_de_donnees(Path,"R_Sph_Bott.mast","[p2.y]",s);
	stream.str("");	
	
	stream << fixed << setprecision(15) << theta[0];
	s= stream.str();  
	modifier_base_de_donnees(Path,"R_Sph_Bott.mast","[theta]",s);
	stream.str("");
	
	modifier_base_de_donnees(Path,"R_Sph_Bott.mast","[nbrcutsx]",to_string((int)((CutsX)/ratio)));
	modifier_base_de_donnees(Path,"R_Sph_Bott.mast","[nbrcutsy]",to_string((int)((CutsY)/ratio)));
	creat_file(Path,"Sphere.mast");
	Add_file_in_the_end(Path ,"R_Sph_Bott.mast",Path,"Sphere.mast");

	chdir(Path.c_str());	
	system("Zrun -B Sphere.mast");
	remove( "R_Sph_Bott.mast" );
	

	
	chdir("../../../../..");
	if(config==0)
   {
       Add_file_in_the_end(PathFSrc+"/Maillage" ,"TieMStoS.inp",Path,"TieM.inp");
   }
   if(config==1)
   {
       Add_file_in_the_end(PathFSrc+"/Maillage" ,"TieMCtoP.inp",Path,"TieM.inp");
      
   }
	
	modifier_base_de_donnees(Path,"TieM.inp","[MS1B]","SBL1B"); 
	modifier_base_de_donnees(Path,"TieM.inp","[MS2B]","SBL2B");
	modifier_base_de_donnees(Path,"TieM.inp","[MS1T]","SBL1T"); 
	modifier_base_de_donnees(Path,"TieM.inp","[MS2T]","SBL2T"); 	 
	T_CutsX=(int)((CutsX)/(3*ratio));
	T_CutsY=T_CutsX;
	p0y[0]=0;
	p1y[0]=dist;
	p2x[0]=0;
	p3x[0]=dist; 	
	for(int i=1;i<=n;i++)
	{		
      string Medi="R_Sph_Med_"+to_string(i)+".mast";
		creat_file(Path,Medi);
		
		Add_file_in_the_end(PathFSrc+"/Maillage" ,"Sph_med.mast",Path,Medi);
	   if(config==0)
      {
       if(IN==0)
       {
       modifier_base_de_donnees(Path,Medi,"c2d4","cax4");
       modifier_base_de_donnees(Path,Medi,"c2d3","cax3");
       }
       else
       {
       modifier_base_de_donnees(Path,Medi,"c2d4","cax8");
       modifier_base_de_donnees(Path,Medi,"c2d3","cax6");
       modifier_base_de_donnees(Path,Medi,"*order 1","*order 2");
       
       }
      }
      else
      {
      if(IN==1)
       {
       modifier_base_de_donnees(Path,Medi,"c2d4","c2d8");
       modifier_base_de_donnees(Path,Medi,"c2d3","c2d6");
       modifier_base_de_donnees(Path,Medi,"*order 1","*order 2");
       }
       
       
      }
		//cout<<"donner les positions du première bloque : ";
		//cin>>p0y>>p1y>>p2x>> p3x;
		p0y[i]=p0y[i-1]+dist;p1y[i]=p1y[i-1]+dist;p2x[i]=p2x[i-1]+dist;p3x[i]=p3x[i-1]+dist;
		stream << fixed << setprecision(15) << p0y[i];
		s= stream.str(); 
		modifier_base_de_donnees(Path,Medi,"[p0.y]",s);
		stream.str("");

		stream << fixed << setprecision(15) << p1y[i];
		s= stream.str();
		modifier_base_de_donnees(Path,Medi,"[p1.y]",s);
		stream.str("");

		stream << fixed << setprecision(15) << p2x[i];
		s= stream.str();
		modifier_base_de_donnees(Path,Medi,"[p2.x]",s);
		stream.str("");

		stream << fixed << setprecision(15) << p3x[i];
		s= stream.str();
		modifier_base_de_donnees(Path,Medi,"[p3.x]",s);
		stream.str("");

		stream << fixed << setprecision(15) << R;
		s= stream.str();
		modifier_base_de_donnees(Path,Medi,"[R]",s);
		stream.str("");

		p6y[i]=R-sqrt(R*R-p3x[i]*p3x[i]);
		theta[i*2-1]=M_PI*1.5+asin(p3x[i]/R);
		stream << fixed << setprecision(15) << p6y[i];
		s= stream.str(); 
		modifier_base_de_donnees(Path,Medi,"[p6.y]",s);
		stream.str("");	
		stream << fixed << setprecision(15) << theta[i*2-1];
		s= stream.str();  
		modifier_base_de_donnees(Path,Medi,"[theta2]",s);
		stream.str("");
		modifier_base_de_donnees(Path,Medi,"[i]",to_string(i));

		p5y[i]=R-sqrt(R*R-p2x[i]*p2x[i]);
		theta[i*2]=M_PI*1.5+asin(p2x[i]/R);
		stream << fixed << setprecision(15) << p5y[i];
		s= stream.str(); 
		modifier_base_de_donnees(Path,Medi,"[p5.y]",s);
		stream.str("");

		stream << fixed << setprecision(15) << theta[i*2];
		s= stream.str();  
		modifier_base_de_donnees(Path,Medi,"[theta1]",s);
		stream.str("");
   	modifier_base_de_donnees(Path,Medi,"[nbrcutsx]",to_string(T_CutsX));
	   modifier_base_de_donnees(Path,Medi,"[nbrcutsy]",to_string(T_CutsY));


		creat_file(Path,"Mesher_t.inp");
		Add_file_in_the_end(PathFSrc+"/Maillage" ,"Mesher.inp",Path,"Mesher_t.inp");
		modifier_base_de_donnees(Path,"Mesher_t.inp","[file]","R_Sph_Med_"+to_string(i)+".geof");
			
		chdir(Path.c_str());		

		string Mesh="Zrun -B "+Medi;
		system(Mesh.c_str());

		system("Zrun -m Mesher_t.inp");
		remove( Medi.c_str() );
		todel="R_Sph_Med_"+to_string(i)+".geof";
		remove( todel.c_str() );
		todel="R_Sph_Med_"+to_string(i)+".msg";
		remove(todel.c_str() );
		remove("Sphere.geof");
		rename( "Sphere1.geof" , "Sphere.geof" );
		chdir("../../../../..");
		modifier_base_de_donnees(Path,"TieM.inp","[WD]",to_string(p2x[i]*3./T_CutsX)); 
		modifier_base_de_donnees(Path,"TieM.inp","[NMS1T]","SMLb1T"+to_string(i)); 
		modifier_base_de_donnees(Path,"TieM.inp","[NMS2T]","SMLb2T"+to_string(i)); 		
		modifier_base_de_donnees(Path,"TieM.inp","[NMS1B]","SMLb1B"+to_string(i)); 
		modifier_base_de_donnees(Path,"TieM.inp","[NMS2B]","SMLb2B"+to_string(i)); 
	   if(config==0)
      {
      	   Add_file_in_the_end(PathFSrc+"/Maillage" ,"TieMStoS.inp",Path,"TieM.inp");
      }
      if(config==1)
      {
      	   Add_file_in_the_end(PathFSrc+"/Maillage" ,"TieMCtoP.inp",Path,"TieM.inp");
            creat_file(Path,"Cube.mast");
            Add_file_in_the_end(PathFSrc+"/Maillage" ,"Cube.mast",Path,"Cube.mast");
            modifier_base_de_donnees(Path,"Cube.mast","[nbr]",to_string(CutsX));
            if(IN==1)
            {
             modifier_base_de_donnees(Path,"Cube.mast","c2d4","c2d8");
             modifier_base_de_donnees(Path,"Cube.mast","*order 1","*order 2");
            }
            
      }
    	modifier_base_de_donnees(Path,"TieM.inp","[MS1T]","SMLu1T"+to_string(i));
		modifier_base_de_donnees(Path,"TieM.inp","[MS2T]","SMLu2T"+to_string(i)); 	   
   	modifier_base_de_donnees(Path,"TieM.inp","[MS1B]","SMLu1B"+to_string(i));
		modifier_base_de_donnees(Path,"TieM.inp","[MS2B]","SMLu2B"+to_string(i)); 	 
   	T_CutsX=max((int)(T_CutsX)/3,7);
	   T_CutsY=T_CutsX; 
	   

		}
		
   creat_file(Path,"Mesher3.inp");
   if(T_Model.config==0)
   {
	Add_file_in_the_end(PathFSrc+"/Maillage" ,"Mesher3StoS.inp",Path,"Mesher3.inp");
   }
   if(T_Model.config==1)
   {
	Add_file_in_the_end(PathFSrc+"/Maillage" ,"Mesher3CtoP.inp",Path,"Mesher3.inp");
   }  
      

	
   creat_file(Path,"Mesher4.inp");
   if(T_Model.config==0)
   {
   Add_file_in_the_end(PathFSrc+"/Maillage" ,"Mesher4StoS.inp",Path,"Mesher4.inp");
   }
   if(T_Model.config==1)
   {
   Add_file_in_the_end(PathFSrc+"/Maillage" ,"Mesher4CtoP.inp",Path,"Mesher4.inp");
   }   
   
	
		
	creat_file(Path,"Mesher2.inp");
	Add_file_in_the_end(PathFSrc+"/Maillage" ,"Mesher2.inp",Path,"Mesher2.inp");
	
	creat_file(Path,"R_Sph_Top.mast");
	Add_file_in_the_end(PathFSrc+"/Maillage" ,"Sph_Top.mast",Path,"R_Sph_Top.mast");
    
   if(config==0)
   {
    if(IN==0)
    {
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","c2d4","cax4");
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","c2d3","cax3");
    }
    else
    {
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","c2d4","cax8");
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","c2d3","cax6");   
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","*order 1","*order 2");       
    }	
	
   }
   else
   {
   if(IN==1)
    {
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","c2d4","c2d8");
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","c2d3","c2d6");
    modifier_base_de_donnees(Path,"R_Sph_Top.mast","*order 1","*order 2");       
    }   
   }
	//cout<<"donner les positions du première bloque : ";
	//cin>>p0y>> p3x;
	p0y[n+1]=p0y[n]+dist; p3x[n+1]=p3x[n];
   stream << fixed << setprecision(15) << p0y[n+1];
	s= stream.str(); 
	modifier_base_de_donnees(Path,"R_Sph_Top.mast","[p0.y]",s);
	stream.str("");

	stream << fixed << setprecision(15) << p3x[n+1];
	s= stream.str();
	modifier_base_de_donnees(Path,"R_Sph_Top.mast","[p3.x]",s);
	stream.str("");


	stream << fixed << setprecision(15) << R;
	s= stream.str();
	modifier_base_de_donnees(Path,"R_Sph_Top.mast","[R]",s);
	stream.str("");

	p6y[n+1]=R-sqrt(R*R-p3x[n+1]*p3x[n+1]);
	theta[2*n+1]=M_PI*1.5+asin(p3x[n+1]/R);
	stream << fixed << setprecision(15) << p6y[n+1];
	s= stream.str(); 
	modifier_base_de_donnees(Path,"R_Sph_Top.mast","[p6.y]",s);
	stream.str("");	
	stream << fixed << setprecision(15) << theta[2*n+1];
	s= stream.str();  
	modifier_base_de_donnees(Path,"R_Sph_Top.mast","[theta]",s);
	stream.str("");
   modifier_base_de_donnees(Path,"R_Sph_Top.mast","[nbrcutsx]",to_string(T_CutsX*3));
   modifier_base_de_donnees(Path,"R_Sph_Top.mast","[nbrcutsy]",to_string(T_CutsY*4));
   modifier_base_de_donnees(Path,"R_Sph_Top.mast","[nbrcutsR]",to_string(T_CutsY*4));

   chdir(Path.c_str());
   system("Zrun -B Cube.mast");
	system("Zrun -B R_Sph_Top.mast");
	system("Zrun -m Mesher2.inp");
	rename("Sphere1.geof" , "Sphere.geof" );
	remove("R_Sph_Top.mast");
	remove("R_Sph_Top.geof");
	remove("R_Sph_Top.msg");
   system("Zrun -m Mesher3.inp");
	remove("Mesher_t.msg");
	remove("Mesher_t.inp");
	remove("Mesher3.msg");
	remove("Mesher2.msg");
	remove("Mesher2.inp");
	remove("Sphere.mast");
	remove("Sphere.msg");
	modifier_base_de_donnees(".","Sphere1.geof","SBL1T","SBL1B");
	modifier_base_de_donnees(".","Sphere1.geof","SBL2T","SBL2B");
	modifier_base_de_donnees(".","Sphere1.geof","SMLb1T","SMLb1B");
	modifier_base_de_donnees(".","Sphere1.geof","SMLb2T","SMLb2B");
	modifier_base_de_donnees(".","Sphere1.geof","SMLu1T","SMLu1B");
	modifier_base_de_donnees(".","Sphere1.geof","SMLu2T","SMLu2B");
	modifier_base_de_donnees(".","Sphere1.geof","STL1T","STL1B");
	modifier_base_de_donnees(".","Sphere1.geof","STL2T","STL2B");
	system("Zrun -m Mesher4.inp");
	remove("Mesher3.inp");	
	remove("Mesher4.msg");
	remove("Mesher4.inp");
   remove("Sphere.geof");
   remove("Sphere1.geof");
	rename("Sphere2.geof" , "Sphere.geof" );
   chdir("../../../../..");
 
	modifier_base_de_donnees(Path,"TieM.inp","[NMS1T]","STL1T"); 
	modifier_base_de_donnees(Path,"TieM.inp","[NMS2T]","STL2T");

	modifier_base_de_donnees(Path,"TieM.inp","[NMS1B]","STL1B"); 
	modifier_base_de_donnees(Path,"TieM.inp","[NMS2B]","STL2B");
	
	modifier_base_de_donnees(Path,"TieM.inp","[WD]",to_string(p3x[n+1]*2.1/T_CutsX)); 
	
	}
	else
	{

	creat_file(Path,"geom_1.mast");
	creat_file(Path,"geom_2.mast");	
	Add_file_in_the_end(PathFSrc+"/Maillage" ,"geom_1.mast",Path,"geom_1.mast");
	Add_file_in_the_end(PathFSrc+"/Maillage" ,"geom_2.mast",Path,"geom_2.mast");
   Add_file_in_the_end(PathFSrc+"/Maillage" ,"Mesher3D.inp",Path,"Mesher3D.inp");
   modifier_base_de_donnees(Path,"geom_2.mast","[nbrXC]",to_string(CutsX));
   modifier_base_de_donnees(Path,"Mesher3D.inp","[nbrXC]",to_string(CutsX*2));   
	chdir(Path.c_str());
	system("Zrun -B geom_1.mast");
	system("Zrun -B geom_2.mast");
	system("Zrun -m Mesher3D.inp");	
	chdir("../../../../..");
	}
	

}

void modifier_base_de_donnees(string Path, string FileName, string
  mot_a_modifier, string nouveau_mot)
{
  string PathFSrc, PathFDst;
  PathFSrc = Path + "/" + FileName;
  PathFDst = Path + "/2" + FileName;
  //char mot_cle[30];

  ifstream fichier(PathFSrc.c_str()); // Flux de lecture
  ofstream flux(PathFDst.c_str()); // Flux d'ecriture

  if (fichier)
  // Si le fichier existe bien
  {
    string ligne;

    while (getline(fichier, ligne))
    // On le lis ligne par ligne
    {
      if (flux)
      // Si le lieu de destination existe ( j'entend par la le dossier )
      {
        size_t index = 0;
        while (true)
        {
          /* Locate the substring to replace. */
          index = ligne.find(mot_a_modifier, index);
          if (index == string::npos)
            break;

          /* Make the replacement. */
          ligne.replace(index, max(mot_a_modifier.size(), nouveau_mot.size()),
            nouveau_mot);

          /* Advance index forward so the next iteration doesn't pick it up as well. */
          index += max(mot_a_modifier.size(), nouveau_mot.size());
        }
        flux << ligne << endl; // On ecrit dans le fichier de destination
      } // Et au passage on le créer si il n'existe pas
      else
      {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
      }
    }
  }
  else
  {
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }

  flux.close();
  fichier.close();
  remove(PathFSrc.c_str());
  rename(PathFDst.c_str(), PathFSrc.c_str());
}

string SimTitle(const ThisModel T_Model)
{
  string Title = "";

  switch (T_Model.I)
  {
    case TWOD:
      Title += "2D";
      break;
    case ThreeD:
      Title += "3D";
      break;
  }

  Title += "_Incr(" + to_string(T_Model.Incr) + ")_Iter(" + to_string(T_Model.Iter) + ")";

  switch (T_Model.C)
  {
    case AvecFrottement:
      Title += "_AF";
      break;
    case SansFrottement:
      Title += "_SF";
      break;
  }



  switch (T_Model.B1.type)
  {
    case Elasti:
      Title += "_E(" + to_string(T_Model.B1.young) + "," + to_string
        (T_Model.B1.poisson) + ")";
      break;
    case Elasto_Plast:
      Title += "_EP";
      break;
  }
  

      switch (T_Model.B2.type)
      {
      case Elasti:
        Title += "_E(" + to_string(T_Model.B2.young) + "," + to_string
          (T_Model.B2.poisson) + ")";
        break;
      case Elasto_Plast:
        Title += "_EP";
        break;
      }

  
  switch (T_Model.IN)
  {
    case Linear:
      Title += "_IL";
      break;
    case Quadratic:
      Title += "_IQ";
      break;
  }

  Title += "_NA(" + to_string(T_Model.MP.normal_augment) + ")-TASF(" + to_string
    (T_Model.MP.tang_aug_scale_factor) + ")-WD(" + to_string(T_Model.MP.warning_dist)
    + ")";
  return Title;

}


void Create_MED(const ThisModel T_Model)
{
  
  string Title = "";
  Title = SimTitle(T_Model);
  string Path = "",Mortar,MS1,MS2;
  Path = OutputPath;
  double R=20.;
   string s;
	stringstream stream;

  switch (T_Model.I)
  {
    case TWOD:
      Path += "/2D";
      break;
    case ThreeD:
      Path += "/3D";
      break;
  }

  switch (T_Model.C)
  {
    case AvecFrottement:
      Path += "/AF";
      Mortar="calcul_MorAF.inp";      
      break;
    case SansFrottement:
      Path += "/SF";
      Mortar="calcul_MorSF.inp";
      break;
  }
  switch (T_Model.B1.type)
  {
    case Elasti:
      MS1="MatBehav_E_S1.inp";
      MS2="MatBehav_E_S2.inp";
      Path += "/E/";
      break;
    case Elasto_Plast:
      MS1="MatBehav_EP_S1.inp";
      MS2="MatBehav_EP_S2.inp";
      Path += "/EP/";
      break;
  }  



 map<string,int> ::iterator  it= mapT.find(Path+Title);
 if(!(it != mapT.end()))
 {

 
  string PathFDest = Path+ to_string(mapT.size()+1);
  
  rek_mkdir(PathFDest);
  rek_mkdir(PathFDest+"/mesh_quality/Data");
  rek_mkdir(PathFDest+"/mesh_quality/Figure");
  creat_file(PathFDest, "calcul.inp");
  creat_file(PathFDest, "MatBehavS1.inp");
  creat_file(PathFDest, "MatBehavS2.inp");
  creat_file(PathFDest, "zset.slurm");
  creat_file(PathFDest, "gnuplot.gnu");
  creat_file(PathFDest, "readUT.py");
  creat_file(PathFDest, "TieM.inp");
  creat_file(PathFDest, "mesh_quality.py");
  
    
  Add_file_in_the_end(PathFSrc, "zset.slurm", PathFDest, "zset.slurm");
  Add_file_in_the_end(PathFSrc, MS1, PathFDest, "MatBehavS1.inp");
  Add_file_in_the_end(PathFSrc, MS2, PathFDest, "MatBehavS2.inp");
  Add_file_in_the_end(PathFSrc, "calcul.inp", PathFDest, "calcul.inp");
  Add_file_in_the_end(PathFSrc, "readUT.py", PathFDest, "readUT.py");
  Add_file_in_the_end(PathFSrc, "gnuplot.gnu", PathFDest, "gnuplot.gnu");
  Add_file_in_the_end(PathFSrc, "mesh_quality.py", PathFDest, "mesh_quality.py");
  bool test;
   switch (T_Model.I)
  {
    case TWOD:
         test=TRUE;
        
        break;
    case ThreeD:
         test=FALSE;
        break;
  }
  
 if(test)
 {
        int cas;
        switch(T_Model.IN)
        {
        case Linear :
               cas=0;
               break;
        case Quadratic :
               cas=1;
               break;        
        }
        
        
        createMesh(PathFDest,R,2,T_Model.CutsX,T_Model.CutsY ,T_Model.config,cas,T_Model.ratio,test);
        Add_file_in_the_end(PathFSrc, "calcul_BC.inp", PathFDest, "calcul.inp");
        Add_file_in_the_end(PathFSrc, "calcul_TB.inp", PathFDest, "calcul.inp");
        Add_file_in_the_end(PathFDest, "TieM.inp", PathFDest, "calcul.inp");
        Add_file_in_the_end(PathFSrc,Mortar, PathFDest, "calcul.inp");
	     if(T_Model.config==0)
        {
        Add_file_in_the_end(PathFSrc, "calcul_MStoS.inp", PathFDest, "calcul.inp");
        }
        if(T_Model.config==1)
        {
        Add_file_in_the_end(PathFSrc, "calcul_MCtoP.inp", PathFDest, "calcul.inp");
         
        }
        
        Add_file_in_the_end(PathFSrc, "calcul_M.inp", PathFDest, "calcul.inp");
        
        modifier_base_de_donnees(PathFDest, "zset.slurm", "[SBATCH]", SForme(to_string(mapT.size()+1),5));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[warning_dist]", to_string (T_Model.MP.warning_dist));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[normal_augment]",to_string(T_Model.MP.normal_augment));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[tang_aug_scale_factor]",to_string(T_Model.MP.tang_aug_scale_factor));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[fric_coeff]",to_string(T_Model.fric_coeff));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[nbrIncrement]", to_string(T_Model.Incr));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[nbrIter]", to_string(T_Model.Iter));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[NDist]", to_string(T_Model.MN));        
        modifier_base_de_donnees(PathFDest, "MatBehavS1.inp", "[young]", to_string(T_Model.B1.young));
        modifier_base_de_donnees(PathFDest, "MatBehavS1.inp", "[poisson]", to_string(T_Model.B1.poisson));
        modifier_base_de_donnees(PathFDest, "MatBehavS2.inp", "[young]", to_string(T_Model.B2.young));
        modifier_base_de_donnees(PathFDest, "MatBehavS2.inp", "[poisson]", to_string(T_Model.B2.poisson));
        if(T_Model.config==0)
        {
        modifier_base_de_donnees(PathFDest, "calcul.inp","plane_strain"," ");
        }
         
 }
 else
 {

   int cas;
   switch(T_Model.IN)
   {
   case Linear :
         cas=0;
         break;
   case Quadratic :
         cas=1;
         break;        
   }
     
   createMesh(PathFDest,R,2,T_Model.CutsX,T_Model.CutsY ,T_Model.config,cas,T_Model.ratio,test);
   
        modifier_base_de_donnees(PathFDest, "zset.slurm", "[SBATCH]", SForme(to_string(mapT.size()+1),5));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[warning_dist]", to_string (T_Model.MP.warning_dist));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[normal_augment]",to_string(T_Model.MP.normal_augment));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[tang_aug_scale_factor]",to_string(T_Model.MP.tang_aug_scale_factor));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[fric_coeff]",to_string(T_Model.fric_coeff));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[nbrIncrement]", to_string(T_Model.Incr));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[nbrIter]", to_string(T_Model.Iter));
        modifier_base_de_donnees(PathFDest, "calcul.inp", "[NDist]", to_string(T_Model.MN));        
        modifier_base_de_donnees(PathFDest, "MatBehavS1.inp", "[young]", to_string(T_Model.B1.young));
        modifier_base_de_donnees(PathFDest, "MatBehavS1.inp", "[poisson]", to_string(T_Model.B1.poisson));
        modifier_base_de_donnees(PathFDest, "MatBehavS2.inp", "[young]", to_string(T_Model.B2.young));
        modifier_base_de_donnees(PathFDest, "MatBehavS2.inp", "[poisson]", to_string(T_Model.B2.poisson)); 
        modifier_base_de_donnees(PathFDest, "calcul.inp","plane_strain"," ");
 }

 Add_file_in_the_end(PathFSrc,"logfile","./","logfile");
 modifier_base_de_donnees( "./","logfile","[ID]", SForme(to_string(mapT.size()+1),5));
 modifier_base_de_donnees( "./","logfile","[Path]", PathFDest);
 modifier_base_de_donnees("./","logfile","[I]", SForme(to_string(T_Model.Incr),3));
 modifier_base_de_donnees("./","logfile","[Cfig]", "StoS");


 
 double CZone=2.0;
 stream.str("");
 stream << fixed << setprecision(1) << T_Model.B1.young;
 s= stream.str(); 
 modifier_base_de_donnees("./","logfile","[Yong1]   ", SForme(s,10));
 stream.str("");
 stream << fixed << setprecision(3) << T_Model.B1.poisson;
 s= stream.str(); 
 modifier_base_de_donnees("./","logfile","[pois1]", SForme(s,7));
 stream.str("");
 stream << fixed << setprecision(1) << T_Model.B2.young;
 s= stream.str();  
 modifier_base_de_donnees("./","logfile","[Yong2]   ",SForme(s,10));
 stream.str("");
 stream << fixed << setprecision(3) << T_Model.B2.poisson;
 s= stream.str();   
 modifier_base_de_donnees("./","logfile","[pois2]", SForme(s,7));
 
 stream.str("");
 stream << fixed << setprecision(5) << CZone/T_Model.CutsX;
 s= stream.str();   
 modifier_base_de_donnees("./","logfile","[T.Mai1]", SForme(s,8));

 stream.str("");
 stream << fixed << setprecision(3) <<T_Model.ratio;
 s= stream.str();   
 modifier_base_de_donnees("./","logfile","[Rat]", SForme(s,5));

 stream.str("");
 stream << fixed << setprecision(1) << T_Model.MP.tang_aug_scale_factor;
 s= stream.str();   
 modifier_base_de_donnees( "./","logfile","[TangASF]  ", SForme(s,11) );
 stream.str("");
 stream << fixed << setprecision(3) << T_Model.MP.warning_dist;
 s= stream.str();   
 modifier_base_de_donnees( "./","logfile","[WDist]",  SForme(s,7));
  stream.str("");
 stream << fixed << setprecision(1) <<T_Model.MP.normal_augment;
 s= stream.str();   
 modifier_base_de_donnees( "./","logfile","[NormalAugm]  ",  SForme(s,14));
 
 stream.str("");
 stream << fixed << setprecision(4) <<T_Model.MN;
 s= stream.str();   
 modifier_base_de_donnees( "./","logfile","[Delta]",  SForme(s,7)); 
// modifier_base_de_donnees("./","logfile","[T.Maill]", to_string(T_Model.Incr));
 modifier_base_de_donnees("./","logfile","[Yld2]", "  --  "); 
 modifier_base_de_donnees("./","logfile","[Yld1]", "  --  "); 



 mapT[PathFDest]=mapT.size()+1;
 
  switch (T_Model.I)
  {
    case TWOD:
      modifier_base_de_donnees( "./","logfile","[Ip]",  "2D");
      break;
    case ThreeD:
      modifier_base_de_donnees( "./","logfile","[Ip]",  "3D");
      break;
  }
  

  switch (T_Model.C)
  {
    case AvecFrottement:
      modifier_base_de_donnees( "./","logfile","[Fr]",  "Avec");
      break;
    case SansFrottement:
      modifier_base_de_donnees( "./","logfile","[Fr]",  "Sans");
      break;
  }

   
  switch (T_Model.IN)
  {
    case Linear:
      modifier_base_de_donnees( "./","logfile","[Inte]", "Lineai");
      break;
    case Quadratic:
      modifier_base_de_donnees( "./","logfile","[Inte]", "Quadra");
      break;
  }

 chdir(PathFDest.c_str());
 system("bash  zset.slurm");
 system("pvbatch mesh_quality.py");
 system("gnuplot gnuplot.gnu");


 int maxIter=0; 
 double temp,pos,maxErreur=0;
 ifstream fichier("./calcul.msg"); // Flux de lecture

 if (fichier)
  {
   string ligne;
   
    while (getline(fichier, ligne))
    {
    size_t index = 0;
    string Stmp;
    int Itmp;
    /* Locate the substring to replace. */
    index = ligne.find(" iter: ", index);
    if (index != string::npos) 
    {
    std::istringstream iss(ligne);
    iss.str(ligne);
    iss >>Stmp>>Itmp;
    maxIter=max(maxIter,Itmp);
    }
    }
  }
  else
  {
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;  
  }


  fichier.close();
  
  ifstream fichier2("./mesh_quality/Data/sig22.dat"); // Flux de lecture

  if (fichier2)
  {
   string ligne;
   getline(fichier2, ligne);
   getline(fichier2, ligne);
   getline(fichier2, ligne);
   getline(fichier2, ligne);
   
    while (getline(fichier2, ligne))
    {

    std::istringstream iss(ligne);
    iss.str(ligne);
    iss >> pos>>temp;
    maxErreur=max(maxErreur,abs(temp));
    }
  }
  else
  {
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }


  fichier2.close();


  
 chdir("../../../../..");
 stream.str("");
 stream << fixed << setprecision(3) << maxErreur*100;
 s= stream.str();  
 modifier_base_de_donnees( "./","logfile","[Errmax] ", SForme(s,9));
 modifier_base_de_donnees("./","logfile","[It]",  SForme(to_string(maxIter),4));

 mapT[PathFDest]=mapT.size()+1;
}

}



void rek_mkdir(string Path)
{

  string temp = "";
  for (unsigned int i = 0; i < Path.size(); i++)
  {
    if (Path[i] == '/')
    {
      temp = Path.substr(0, i);
      cout << temp;
      mkdir(temp.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
  }
  mkdir(Path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

}



FILE *creat_file(string Path, string FileName)
{
  FILE *fichier = NULL;
  Path = Path + "/" + FileName;
  fichier = fopen(Path.c_str(), "w");
  fclose(fichier);
  return fichier;
}

int Add_file_in_the_end(string PathFSrc, string FileNameSrc, string PathFDest,
  string FileNameDest)
{
  FILE *fSrc = NULL;
  FILE *fDest = NULL;
  PathFSrc = PathFSrc + "/" + FileNameSrc;
  PathFDest = PathFDest + "/" + FileNameDest;
  char ligne[1000];
  if ((fSrc = fopen(PathFSrc.c_str(), "r+")) == NULL)
  {
    return 1;
  }
  if ((fDest = fopen(PathFDest.c_str(), "a+")) == NULL)
  {
    fclose(fSrc);
    return 2;
  }

  fgets(ligne, 1000, fSrc);
  while (!feof(fSrc))
  {
    fputs(ligne, fDest);
    fgets(ligne, 1000, fSrc);
  }
  fclose(fDest);
  fclose(fSrc);

  printf("\nLa copie est terminee.\n");

  return 0;

}


string removeSpaces(string str)
{
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  return str;
}


GtkWidget *CreateWin(int tx, int ty, int argc, char **argv)
{
  GtkWidget *pWindow;
  GtkWidget *pHBox[30];
  GtkWidget *pFrame[30];
  GtkWidget *pVBoxFrame[30];
  GtkWidget *pButton[30];
  GtkWidget *pLabel[30];
  GtkWidget *pTable;
  GtkWidget *check[30];
  GtkWidget *pEntry[30];
  gtk_init(&argc, &argv);
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
  gtk_window_set_title(GTK_WINDOW(pWindow), "Auto_generator_SAIDI");
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 220, 850);
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit),
    NULL);
  pTable = gtk_table_new(ty, tx, TRUE);
  pFrame[0] = gtk_frame_new("Modele");
  gtk_table_attach_defaults(GTK_TABLE(pTable), pFrame[0], 0, tx, 0, 4);
  pVBoxFrame[0] = gtk_vbox_new(TRUE, 0);
  pHBox[0] = gtk_hbox_new(FALSE, 0);
  pLabel[0] = gtk_label_new("Implementation : ");
  gtk_box_pack_start(GTK_BOX(pHBox[0]), pLabel[0], FALSE, TRUE, 0);
  check[0] = gtk_check_button_new_with_label("2D");
  gtk_box_pack_start(GTK_BOX(pHBox[0]), check[0], TRUE, TRUE, 0);
  check[1] = gtk_check_button_new_with_label("3D");
  gtk_box_pack_start(GTK_BOX(pHBox[0]), check[1], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[0]), pHBox[0], TRUE, FALSE, 0);
  pHBox[1] = gtk_hbox_new(FALSE, 0);
  pLabel[1] = gtk_label_new("Frottement : ");
  gtk_box_pack_start(GTK_BOX(pHBox[1]), pLabel[1], FALSE, TRUE, 0);
  check[2] = gtk_check_button_new_with_label("Sans");
  gtk_box_pack_start(GTK_BOX(pHBox[1]), check[2], TRUE, TRUE, 0);
  check[3] = gtk_check_button_new_with_label("Avec");
  gtk_box_pack_start(GTK_BOX(pHBox[1]), check[3], FALSE, TRUE, 10);
  pLabel[7] = gtk_label_new("Coef_Frot : ");
  gtk_box_pack_start(GTK_BOX(pHBox[1]), pLabel[7], FALSE, TRUE, 0);
  pEntry[5] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[1]), pEntry[5], FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[0]), pHBox[1], TRUE, FALSE, 0);
  pHBox[2] = gtk_hbox_new(FALSE, 0);
  pLabel[2] = gtk_label_new("Nombre d'incrément : ");
  gtk_box_pack_start(GTK_BOX(pHBox[2]), pLabel[2], FALSE, TRUE, 50);
  pEntry[0] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[2]), pEntry[0], TRUE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[5]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[0] ); 
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[0]), pHBox[2], TRUE, FALSE, 0);
  pHBox[8] = gtk_hbox_new(FALSE, 0);
  pLabel[6] = gtk_label_new("Nombre d'itération : ");
  gtk_box_pack_start(GTK_BOX(pHBox[8]), pLabel[6], FALSE, TRUE, 55);
  pEntry[4] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[8]), pEntry[4], TRUE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[0]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[4] ); 
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[0]), pHBox[8], TRUE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pFrame[0]), pVBoxFrame[0]);
  pFrame[4] = gtk_frame_new("Maillage");
  gtk_table_attach_defaults(GTK_TABLE(pTable), pFrame[4], 0, tx, 4, 7);
  pVBoxFrame[4] = gtk_vbox_new(TRUE, 0);
  pHBox[9] = gtk_hbox_new(TRUE, 0);
  pLabel[10] = gtk_label_new("Configuration : ");
  gtk_box_pack_start(GTK_BOX(pHBox[9]), pLabel[10], TRUE, TRUE, 0);
  check[10] = gtk_check_button_new_with_label("Sphere-Sphere");
  gtk_box_pack_start(GTK_BOX(pHBox[9]), check[10], TRUE, TRUE, 0);
  check[11] = gtk_check_button_new_with_label("Cyliandre-Plan");
  gtk_box_pack_start(GTK_BOX(pHBox[9]), check[11], FALSE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[4]), pHBox[9], TRUE, FALSE, 0);
  pHBox[10] = gtk_hbox_new(TRUE, 0);
  pLabel[11] = gtk_label_new("Interpolation : ");
  gtk_box_pack_start(GTK_BOX(pHBox[10]), pLabel[11], FALSE, TRUE, 0);
  check[12] = gtk_check_button_new_with_label("Lineaire");
  gtk_box_pack_start(GTK_BOX(pHBox[10]), check[12], TRUE, TRUE, 0);
  check[13] = gtk_check_button_new_with_label("Quadratique");
  gtk_box_pack_start(GTK_BOX(pHBox[10]), check[13], FALSE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[4]), pHBox[10], TRUE, FALSE, 0);
  pHBox[13] = gtk_hbox_new(FALSE, 0);
  pLabel[8] = gtk_label_new("Taille du maillage : ");
  gtk_box_pack_start(GTK_BOX(pHBox[13]), pLabel[8], FALSE, TRUE, 55);
  pEntry[7] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[13]), pEntry[7], TRUE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[4]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[25] );   
  pLabel[25] = gtk_label_new("Ratio : ");
  gtk_box_pack_start(GTK_BOX(pHBox[13]), pLabel[25], FALSE, TRUE, 55);
  pEntry[25] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[13]), pEntry[25], TRUE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[25]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[7] );   
  
  
  
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[4]), pHBox[13], TRUE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pFrame[4]), pVBoxFrame[4]);
  pFrame[1] = gtk_frame_new("Comportement");
  gtk_table_attach_defaults(GTK_TABLE(pTable), pFrame[1], 0, tx, 7, 9);
  pVBoxFrame[1] = gtk_vbox_new(TRUE, 0);
  pHBox[3] = gtk_hbox_new(TRUE, 0);
  check[4] = gtk_check_button_new_with_label("Comportement élastique");
  gtk_box_pack_start(GTK_BOX(pHBox[3]), check[4], TRUE, TRUE, 0);
  check[5] = gtk_check_button_new_with_label("Comportement élasto-plastique");
  gtk_box_pack_start(GTK_BOX(pHBox[3]), check[5], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[1]), pHBox[3], TRUE, FALSE, 0);
  pHBox[15] = gtk_hbox_new(FALSE, 0);
  pLabel[14] = gtk_label_new("E1 : ");
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pLabel[14], FALSE, TRUE, 0);
  pEntry[14] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pEntry[14], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[7]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[14] ); 
  pLabel[15] = gtk_label_new("mu1 : ");
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pLabel[15], FALSE, TRUE, 0);
  pEntry[15] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pEntry[15], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[14]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[15] );   
  pLabel[16] = gtk_label_new("E2 : ");
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pLabel[16], FALSE, TRUE, 0);
  pEntry[16] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pEntry[16], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[15]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[16] ); 
  pLabel[17] = gtk_label_new("mu2 : ");
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pLabel[17], FALSE, TRUE, 0);
  pEntry[17] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[15]), pEntry[17], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[16]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[17] );   
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[1]), pHBox[15], TRUE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pFrame[1]), pVBoxFrame[1]);
  pFrame[2] = gtk_frame_new("Chargement");
  gtk_table_attach_defaults(GTK_TABLE(pTable), pFrame[2], 0, tx, 9, 11);
  pVBoxFrame[2] = gtk_vbox_new(TRUE, 0);
  check[6] = gtk_check_button_new_with_label("Monotone");
  pHBox[4] = gtk_hbox_new(FALSE, 40);
  gtk_box_pack_start(GTK_BOX(pHBox[4]), check[6], FALSE, TRUE, 0);
  pLabel[11] = gtk_label_new("Normal : ");
  gtk_box_pack_start(GTK_BOX(pHBox[4]), pLabel[11], FALSE, TRUE, 0);
  pEntry[12] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[4]), pEntry[12], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[17]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[12] ); 
  pLabel[12] = gtk_label_new("Tangentiel : ");
  gtk_box_pack_start(GTK_BOX(pHBox[4]), pLabel[12], FALSE, TRUE, 0);
  pEntry[13] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[4]), pEntry[13], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[12]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[13] );   
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[2]), pHBox[4], TRUE, FALSE, 0);
  pHBox[14] = gtk_hbox_new(FALSE, 40);
  check[7] = gtk_check_button_new_with_label("Cyclique");
  gtk_box_pack_start(GTK_BOX(pHBox[14]), check[7], FALSE, TRUE, 0);
  pLabel[9] = gtk_label_new("Normal : ");
  gtk_box_pack_start(GTK_BOX(pHBox[14]), pLabel[9], FALSE, TRUE, 0);
  pEntry[10] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[14]), pEntry[10], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[13]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[10] );   
  pLabel[10] = gtk_label_new("Tangensiel : ");
  gtk_box_pack_start(GTK_BOX(pHBox[14]), pLabel[10], FALSE, TRUE, 0);
  pEntry[11] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[14]), pEntry[11], FALSE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[10]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[11] );     
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[2]), pHBox[14], TRUE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pFrame[2]), pVBoxFrame[2]);
  pFrame[3] = gtk_frame_new("Mortar parametre");
  gtk_table_attach_defaults(GTK_TABLE(pTable), pFrame[3], 0, tx, 11, 14);
  pVBoxFrame[3] = gtk_vbox_new(TRUE, 0);
  pHBox[5] = gtk_hbox_new(TRUE, 0);
  pLabel[3] = gtk_label_new("auto_factor : ");
  gtk_box_pack_start(GTK_BOX(pHBox[5]), pLabel[3], TRUE, TRUE, 0);
  pEntry[0] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[5]), pEntry[0], TRUE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[11]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[0] );     
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[3]), pHBox[5], TRUE, FALSE, 0);
  pHBox[6] = gtk_hbox_new(TRUE, 0);
  pLabel[4] = gtk_label_new("tang_aug_scale_factor : ");
  gtk_box_pack_start(GTK_BOX(pHBox[6]), pLabel[4], TRUE, TRUE, 0);
  pEntry[2] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[6]), pEntry[2], TRUE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[0]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[2] );     
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[3]), pHBox[6], TRUE, FALSE, 0);
  pHBox[7] = gtk_hbox_new(TRUE, 0);
  pLabel[5] = gtk_label_new("warning_dist : ");
  gtk_box_pack_start(GTK_BOX(pHBox[7]), pLabel[5], TRUE, TRUE, 0);
  pEntry[3] = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(pHBox[7]), pEntry[3], TRUE, TRUE, 0);
  g_signal_connect (  G_OBJECT (pEntry[2]), "activate",  G_CALLBACK (cb_activate), (GtkEntry *) pEntry[3] );   
  gtk_box_pack_start(GTK_BOX(pVBoxFrame[3]), pHBox[7], TRUE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pFrame[3]), pVBoxFrame[3]);
  pButton[0] = gtk_button_new_with_label("Valider");
  gtk_table_attach_defaults(GTK_TABLE(pTable), pButton[0], tx - 3, tx, 14, 15);
  g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(on_copier_button), (GtkWidget*)pTable);
  gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));
  return pWindow;
  
  
  
}


void lancer(vector < int >& nbrIncr, vector < int >& nbrIter,vector < int >& Tmesh, vector < double >& MpNAug, vector < double >& MpTASFac, vector < double >& MpWDist, vector < double >& B1young, 	vector < double>& B1poisson, vector < double >& B2young, vector < double >& B2poisson, vector < double >& MN, vector < double >& MT, vector < double >& CN, vector < double >& CT)
{
  for (unsigned int i = 0; i < nbrIncr.size(); i++)
  {
    for (unsigned int j = 0; j < nbrIter.size(); j++)
    {
      for (unsigned int u = 0; u < MpNAug.size(); u++)
      {
        for (unsigned int v = 0; v < MpTASFac.size(); v++)
        {
          for (unsigned int k = 0; k < MpWDist.size(); k++)
          {
            for (unsigned int l = 0; l < B1young.size(); l++)
            {
              for (unsigned int n = 0; n < B1poisson.size(); n++)
              {
                for (unsigned int m=0; m < B2young.size(); m++)
                {
                  for (unsigned int p = 0; p < B2poisson.size() ; p++)
                  {
                    for (unsigned int w = 0; w < MN.size(); w++)
                    {
                      for (unsigned int g = 0; g < MT.size(); g++)
                      {
                        for (unsigned int y = 0; y < CN.size(); y++)
                        {
                          for (unsigned int t = 0; t < CT.size(); t++)
                          {
                           for (unsigned int z = 0; z < Tmesh.size(); z++)
                           {
                         
                            T_Model.MP.normal_augment = MpNAug[u];
                            T_Model.MP.tang_aug_scale_factor = MpTASFac[v];
                            T_Model.MP.warning_dist = MpWDist[k];
                            T_Model.B1.young = B1young[l];
                            T_Model.B1.poisson = B1poisson[n];
                            T_Model.B2.young = B2young[m];
                            T_Model.B2.poisson = B2poisson[p];
									 T_Model.Incr=nbrIncr[i];
									 T_Model.Iter=nbrIter[j];
                            T_Model.CutsX=Tmesh[z];
                            T_Model.CutsY=Tmesh[z];
                            T_Model.MN=MN[w];
                            T_Model.MT=MT[g];
                            Create_MED(T_Model);
                           }
                          }
                        }
                      }
                    }
                  }

                }
              }

            }
          }

        }
      }
    }
  }

}


/* Fonction callback executee lors du signal "clicked" */
void on_copier_button(GtkWidget *PButton, gpointer data)
{
  T_Model.fric_coeff=0.;
  GtkWidget *pFrame;
  GtkWidget *pVBoxFrame;
  GtkWidget *pHBox;
  GtkWidget *pEntry;
  GList *pList[5];
  GtkWidget *check;
  string s;
  pList[0] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
  vector < int > Dataint[5];
  vector < double > Datadouble[20];
  // Mortar parametre
  pList[0] = g_list_next(pList[0]);
  pFrame = GTK_WIDGET(pList[0]->data);
  pList[1] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pFrame));
  pVBoxFrame = GTK_WIDGET(pList[1]->data);
  //-------------
  pList[2] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pVBoxFrame));
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[1] = extract < double > (s);
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[2] = extract < double > (s);
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[3] = extract < double > (s);
  // Chargement
  pList[0] = g_list_next(pList[0]);
  pFrame = GTK_WIDGET(pList[0]->data);
  pList[1] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pFrame));
  pVBoxFrame = GTK_WIDGET(pList[1]->data);
  //-------------
  pList[2] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pVBoxFrame));
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    cout << "monotoneok" << endl;
  else
    cout << "monotoneNOk" << endl;
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[4] = extract < double > (s);
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[5] = extract < double > (s);
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE) cout << "cycliqueok" << endl;
  else cout << "cycliqueNOk" << endl;
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[6] = extract < double > (s);
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[7] = extract < double > (s);

  // Comportement
  pList[0] = g_list_next(pList[0]);
  pFrame = GTK_WIDGET(pList[0]->data);
  pList[1] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pFrame));
  pVBoxFrame = GTK_WIDGET(pList[1]->data);
  //-------------
  pList[2] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pVBoxFrame));
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Comportement.Elasti = TRUE;
  else
    This_Comportement.Elasti = FALSE;
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Comportement.Elasto_Plast = TRUE;
  else
    This_Comportement.Elasto_Plast = FALSE;
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[8] = extract < double > (s);
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[9] = extract < double > (s);
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[10] = extract < double > (s);
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[11] = extract < double > (s);

  // Maillage
  pList[0] = g_list_next(pList[0]);
  pFrame = GTK_WIDGET(pList[0]->data);
  pList[1] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pFrame));
  pVBoxFrame = GTK_WIDGET(pList[1]->data);
  //-------------
  pList[2] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pVBoxFrame));
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Maillage.StoS = TRUE;
  else
    This_Maillage.StoS = FALSE;
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Maillage.CtoP = TRUE;
  else
    This_Maillage.CtoP = FALSE;
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Maillage.IL = TRUE;
  else
    This_Maillage.IL = FALSE;
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Maillage.IQ = TRUE;
  else
    This_Maillage.IQ = FALSE;
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Dataint[0] = extract < int > (s);

  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[14] = extract < double > (s);
  if(Datadouble[14].size()!=0) T_Model.ratio=Datadouble[14][0];
  else T_Model.ratio=1.0;
  
  // Modele
  pList[0] = g_list_next(pList[0]);
  pFrame = GTK_WIDGET(pList[0]->data);
  pList[1] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pFrame));
  pVBoxFrame = GTK_WIDGET(pList[1]->data);
  //-------------
  pList[2] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pVBoxFrame));
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Model.TwoD = TRUE;
  else
    This_Model.TwoD = FALSE;
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Model.ThreD = TRUE;
  else
    This_Model.ThreD = FALSE;
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Model.SansFrottement = TRUE;
  else
    This_Model.SansFrottement = FALSE;
  pList[3] = g_list_next(pList[3]);
  check = GTK_WIDGET(pList[3]->data);
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)) == TRUE)
    This_Model.AvecFrottement = TRUE;
  else
    This_Model.AvecFrottement = FALSE;
  pList[3] = g_list_next(pList[3]);
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Datadouble[13] = extract < double > (s);
  if(Datadouble[13].size()!=0) T_Model.fric_coeff=Datadouble[13][0];

  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Dataint[1] = extract < int > (s);
  //-------------
  pList[2] = g_list_next(pList[2]);
  pHBox = GTK_WIDGET(pList[2]->data);
  pList[3] = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pHBox));
  pList[3] = g_list_next(pList[3]);
  pEntry = GTK_WIDGET(pList[3]->data);
  s = gtk_entry_get_text(GTK_ENTRY(pEntry));
  s = removeSpaces(s);
  Dataint[2] = extract < int > (s);
  

  if(Dataint[2].size()*Dataint[1].size()*Dataint[0].size()*Datadouble[1].size()*Datadouble[2].size()*Datadouble[3].size()*Datadouble[4].size()*Datadouble[5].size()*Datadouble[6].size()*Datadouble[7].size()*Datadouble[8].size()*Datadouble[9].size()*Datadouble[10].size()*Datadouble[11].size()*Datadouble[13].size() !=0)
  {


  if (This_Model.TwoD == TRUE)
  {
    T_Model.I = TWOD;
    if (This_Model.AvecFrottement == TRUE)
    {
      T_Model.C = AvecFrottement;
      if (This_Maillage.IL == TRUE)
      {
      
        T_Model.IN = Linear;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		  

      }
      if (This_Maillage.IQ == TRUE)
      {
        T_Model.IN = Quadratic;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		  
      }
    }
    if (This_Model.SansFrottement == TRUE)
    {
      T_Model.C = SansFrottement;
      if(This_Maillage.StoS ==TRUE)
      {
       T_Model.config=0;
      if (This_Maillage.IL == TRUE)
      {
        T_Model.IN = Linear;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        }
      if (This_Maillage.IQ == TRUE)
      {
        T_Model.IN = Quadratic;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        
        }
    }
    if(This_Maillage.CtoP ==TRUE)
    {
    T_Model.config=1;
       if (This_Maillage.IL == TRUE)
      {
        T_Model.IN = Linear;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        }
      if (This_Maillage.IQ == TRUE)
      {
        T_Model.IN = Quadratic;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        
        }    
    
    
    }
    
        
    }



  }

  if (This_Model.ThreD == TRUE)
  {
    T_Model.I = ThreeD;
   if (This_Model.AvecFrottement == TRUE)
    {
      T_Model.C = AvecFrottement;
      if (This_Maillage.IL == TRUE)
      {
      
        T_Model.IN = Linear;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		  

      }
      if (This_Maillage.IQ == TRUE)
      {
        T_Model.IN = Quadratic;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		  
      }
    }
    if (This_Model.SansFrottement == TRUE)
    {
      T_Model.C = SansFrottement;
      if(This_Maillage.StoS ==TRUE)
      {
       T_Model.config=0;
      if (This_Maillage.IL == TRUE)
      {
        T_Model.IN = Linear;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        }
      if (This_Maillage.IQ == TRUE)
      {
        T_Model.IN = Quadratic;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        
        }
    }
    if(This_Maillage.CtoP ==TRUE)
    {
    T_Model.config=1;
       if (This_Maillage.IL == TRUE)
      {
        T_Model.IN = Linear;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        }
      if (This_Maillage.IQ == TRUE)
      {
        T_Model.IN = Quadratic;
        if (This_Comportement.Elasti) {T_Model.B1.type =Elasti;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}
        if (This_Comportement.Elasto_Plast) {T_Model.B1.type =Elasto_Plast;lancer(Dataint[1],Dataint[2] ,Dataint[0],Datadouble[1], Datadouble[2], Datadouble[3], Datadouble[8], Datadouble[9], Datadouble[10], Datadouble[11], Datadouble[4], Datadouble[5], Datadouble[6], Datadouble[7]);}		        
        }    
    
    
    }
    
        
    }



  }

  }



}
