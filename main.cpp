#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>
#include <QTextStream>
#include <argumentlist.h>

void processFile(QString filename, bool verbose) {
   if (verbose)
      qDebug() << QString("Do something chatty with %1.")
                         .arg(filename);
   else
      qDebug() << filename;
}

void runTestOnly(QStringList & listOfFiles, bool verbose) {
   foreach (const QString &current, listOfFiles) { 
      processFile(current, verbose);
   }
}

void printHelpDisplay() {
   QTextStream cout(stdout);
   cout << "DISKUSAGE -bkicia ECE 3574 Homework 3 (2014 Oct 6)\n\n";
   cout << "usage: \t./diskusage [DepthArg] [UnitArg] [TypeArg] [file/directory/symbolicLink...]\nReports the amount of disk space used in the files(s), director(ies), and/or symbolic link(s)\n\n";    
   cout << "Depth Argument: \n-depth=all \tPerform no filtering based on depth \n-depth=<uint> \tShow no resources more than <uint> levels deep\n\n";
   cout << "Unit Argument: \n-b \t\tSizes are shown in bytes\n-k \t\tSizes are shown in kilobytes\n-m \t\tSizes are shown in megabytes\n\n";
   cout << "Type Argument: \n-f \t\tAllows only files to be shown\n-d \t\tAllows only directories to be shown\n-s \t\tAllows only symbolic links to be shown\n-fds \t\tAllows files, directories, & symbolic links to be shown\n-fd \t\tAllows files and directories to be shown\n-fs \t\tAllows files and symbolic links to be shown\n-ds \t\tAllows directories and symbolic links to be shown\n\n";
}

bool depthIsValid(QString depth)  {
   if (depth == "-depth=all") 
      ;//run function for print out all
   else if (depth.mid(0, 7) == "-depth=") {
      depth.remove(0,7);
      uint searchDepth = depth.toInt();
      if ((depth == (QString::number(searchDepth))) && depth>=0)
         ;//run function for print out int
      else
         return false;
   }
   else
      return false;
   return true;
}

bool sizeDisplayIsValid(QString sizeDisplay) {
   if (sizeDisplay == "-b")
      ;//print in bytes
   else if (sizeDisplay == "-k")
      ;//print in kilobytes
   else if (sizeDisplay == "-m")
      ;//print in megabytes
   else 
      return false;
   return true;
}

bool typeArgIsValid(QString typeArg) {
   if (typeArg.mid(0,1) == "-")  {
      typeArg.remove(0,1);
      if (typeArg.isEmpty())
         return false;
      if (typeArg.contains('f'))  {
         typeArg.remove('f');
         ;//allow files to be shown
      }
      if (typeArg.contains('d'))  {
         typeArg.remove('d');
         ;//allow directories to be shown
      }
      if (typeArg.contains('s'))  {
         typeArg.remove('s');
         ;//allow symbolic links to be shown
      }
      if (!typeArg.isEmpty())
         return false;
   }
   else
      return false;
   return true;
}

int main( int argc, char * argv[] ) {
   ArgumentList al(argc, argv);       /* Instantiate the ArgumentList with command line args. */
    QTextStream cout(stdout);
   if (al.size() <= 4)  {
      printHelpDisplay();
      return 0;
   }
   QString appname = al.takeFirst();  /* Inherited from QStringList - first item in the list is the name of the executable. */
   QString depth = al.takeFirst();
   bool depthCheckAndSet = depthIsValid(depth);
   if (!depthCheckAndSet)  {
      printHelpDisplay();
      return 0;
   }

   QString sizeDisplay = al.takeFirst();
   bool sizeCheckAndSet = sizeDisplayIsValid(sizeDisplay);
   if (!sizeCheckAndSet)  {
      printHelpDisplay();
      return 0;
   }

   QString typeArg = al.takeFirst();
   bool typeCheckAndSet = typeArgIsValid(typeArg);
   if (!typeCheckAndSet)   {
      printHelpDisplay();
      return 0;
   }

   QString resource = al.takeFirst();

   //run for "resource"


   qDebug() << "Running " << appname;
   bool verbose = al.getSwitch("-v");
   bool testing = al.getSwitch("-t"); /* Now all switches have been removed from the list. Only filenames remain.*/
   if (testing) {
      runTestOnly(al, verbose);       /* ArgumentList can be used in place of QStringList. */
      return 0;
   } else {
      qDebug() << "This Is Not A Test";
   }
}

