// Marisa Petrusky 06/04/19 Merges ROOT files

// argc = No. of files 
// argv = Array of file numbers
void treemerge(int argc, int argv[])
{
	gDirectory->DeleteAll();
	
	TChain ch("T");

	for (int i=0; i < argc; i++)
	{
		TString infile;
		infile = Form("/home/marisa/rootfiles/test_%d.root",argv[i]);
		ch.Add(infile);
	}

	ch.Merge("mergedtests.root");
}
