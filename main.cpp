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

int main( int argc, char * argv[] ) {
   ArgumentList al(argc, argv);       /* Instantiate the ArgumentList with command line args. */
   if (al.size() <= 4)  {
      printHelpDisplay();
      return 0;
      //print "help"
   }
   QString appname = al.takeFirst();  /* Inherited from QStringList - first item in the list is the name of the executable. */
   QString depth = al.takeFirst();
   QString sizeDisplay = al.takeFirst();
   QString typeArg = al.takeFirst();
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

