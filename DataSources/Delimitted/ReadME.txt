Delimitted Data Source for Ultimate Grid/MFC

This readme describe the use of the Delimitted DataSource in Ultimate Grid for MFC.  

The Delimitted data source is contained in the files UGDelim.cpp and UGDelim.h.

The Delimitted data source is an import/export filter for reading and writing delimited text files with Ultimate Grid.  By default the Delimitted data source is setup to be comma delimmited but can be easily configured (at the time of instantiation) to read any delimmited format by specifying the delimmiter, quote characters and characters that are to be quoted.  


The data source does keep an internal dirty flag and will notify you through OnDataSourceNotify when a file is being closed that may need to be	saved.