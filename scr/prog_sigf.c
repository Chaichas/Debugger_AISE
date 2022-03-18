void lance_erreur_segmentation() 
{ 
 int *pointeur_dangereux=(int *) 100; 
 int test=*pointeur_dangereux; 
} 

int main(int argc, char ** argv) 
{ 
 lance_erreur_segmentation(); 
 return 0; 
}
