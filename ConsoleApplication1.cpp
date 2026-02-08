
#include <iostream>
#include <vector>
using namespace std;
struct FileNode {
	string name;
	string type;
	int date;
	int size;
	FileNode* Next;
	FileNode(string n, string t, int s, int d) :name(n), type(t), size(s),
		date(d), Next(nullptr) {}
};
struct Folder {
	string name;
	vector <Folder*> children;
	FileNode* files;
	Folder* Next;
	Folder(string n) :name(n), files(nullptr) {}
};
void traversal(Folder* node, int depth = 0) {
	for (int i = 0;i < depth;i++)
		cout << "  ";
	cout << node->name << endl;
	for (Folder* child : node->children)
		traversal(child, depth + 1);
}
void printTree(Folder* node, int depth = 0) {
	for (int i = 0;i < depth;i++)
		cout << " ";
	cout << node->name << endl;
	FileNode* files = node->files;
	while (files != nullptr) {
		for (int i = 0;i < depth;i++)
			cout << "     " << files->name << endl;
		files = files->Next;
	}
	for (Folder* child : node->children) {
		printTree(child, depth + 1);
	}
}
int depth(Folder* node)
{
	if (node == nullptr)
		return 0;
	int d = 0;
	for (Folder* child : node->children) {
		int temp = depth(child);
		if (temp > d)
			d = temp;
	}
	return d + 1;
}
void addfolder(Folder* folder, string name) {
	Folder* newFolder = new Folder(name);
	folder->children.push_back(newFolder);
}
void AddFile(Folder* folder, string name, string type, int size, int date) {
	FileNode* newfile = new FileNode(name, type, size, date);
	newfile->Next = folder->files;
	folder->files = newfile;
}
void deletefolder(Folder* folder, string name)
{
	if (folder == nullptr) return;

	for (int i = 0; i < folder->children.size(); i++)
	{
		if (folder->children[i]->name == name)
		{
			delete folder->children[i];
			for (int j = i; j < folder->children.size() - 1; j++)
			{
				folder->children[j] = folder->children[j + 1];
			}
			folder->children.resize(folder->children.size() - 1);
			return;
		}
	}
	for (Folder* child : folder->children)
	{
		deletefolder(child, name);
	}
}
void deleteFile(Folder* folder, string name)
{
	FileNode* p, * q;
	p = folder->files;
	q = nullptr;
	if (p == nullptr)
		return;
	if (p->name == name) {
		folder->files = p->Next;
		delete p;
		return;
	}
	while (p != nullptr && p->name != name) {
		q = p;
		p = p->Next;
	}
	if (p != nullptr) {
		q->Next = p->Next;
		delete p;
	}
}
FileNode* searchfile(Folder* folder, string name) {
	if (folder == nullptr)return nullptr;
	FileNode* p = folder->files;
	while (p) {
		if (p->name == name)
			return p;
		p = p->Next;
	}
	return nullptr;
}
void printFiles(Folder* folder) {
	FileNode* p = folder->files;
	while (p) {
		cout << "  (" << p->name << " ," << p->size << "  ," << p->date << ", " << p->type << ")" << endl;
		p = p->Next;
	}

}
void sortfiles(Folder* folder) {
	FileNode* p = folder->files;
	if (p == nullptr)return;
	bool swapped = false;
	while (p->Next != nullptr)
	{
	     if(p->size > p->Next->size)
		 {
		    swap(p->size, p->Next->size);
			swap(p->date, p->Next->date);
			swap(p->name, p->Next->name);
			swap(p->type, p->Next->type);
			swapped = true;
		 }
		p = p->Next;
	}
}
void folderstotalsize(Folder* folder) {
	FileNode* p = folder->files;
	int total = 0;
	while (p) {
		total += p->size;
		p = p->Next;
	}
	cout << "the total size of folder is:" << total << endl;
}
Folder* searchfolder(Folder* root, string name) {
	if (root == nullptr)
		return nullptr;
	if (root->name == name)
		return root;
	for (Folder* child : root->children) {
		Folder* p = searchfolder(child, name);
		if (p != nullptr)
			return p;
	}
	return nullptr;
}
int countFolder(Folder* folder,int count=1)
{
	if (folder == nullptr)
		return 0;
for (Folder* child : folder->children)
{
		countFolder(child, count++);
}
return count;
}
int main()
{
	int x;
	string foldername;
	int choice;
	int fsize, fdate;
	string fname, ftype;
	Folder* root = new Folder("root");
	Folder* pics = new Folder("picture");
	Folder* docs = new Folder("documents");
	Folder* uni = new Folder("uni");
	Folder* projects = new Folder("projects");
	Folder* saved = new Folder("saved");
	root->children.push_back(docs);
	root->children.push_back(pics);
	docs->children.push_back(uni);
	docs->children.push_back(projects);
	pics->children.push_back(saved);
	AddFile(pics, "videos", "pictures", 567, 1345);
	AddFile(pics, "recents", "pictures", 789, 1401);
	AddFile(pics, "camera", "pictures", 678, 1403);
	AddFile(pics, "telegram", "pictures", 950, 1398);
	AddFile(docs, "downloads", "data", 890, 1367);
	AddFile(uni, "cards", "text", 657, 1389);
	Folder* selectedFolder = nullptr;
	FileNode* q = nullptr;
	Folder* p = nullptr;
	do {
		printTree(root);
		cout << "\n***file operations***\n" << endl;
		cout << "1.AddFile:" << endl;
		cout << "2.DeleteFile:" << endl;
		cout << "3.SearchFile:" << endl;
		cout << "4.SortFile:" << endl;
		cout << "5.estimate the folder'size :" << endl;
		cout << "6.Print Files:" << endl;
		cout << "\n***Folder Operatino***\n" << endl;
		cout << "7.SearchFolders:" << endl;
		cout << "8.estimate the tree's depth:" << endl;
		cout << "9.AddFolder:" << endl;
		cout << "10.DeleteFolder:" << endl;
		cout << "11.traversal:" << endl;
		cout << "12.counting folders:" << endl;
		cout << "0.exit." << endl;
		cout << "choose:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "folder name:";
			cin >> foldername;
			selectedFolder = searchfolder(root, foldername);
			if (!selectedFolder) {
				cout << "folder not found" << endl;
				break;
			}
			cout << "file name:";
			cin >> fname;
			cout << "file type:";
			cin >> ftype;
			cout << "file size:";
			cin >> fsize;
			cout << "file creation date:";
			cin >> fdate;
			AddFile(selectedFolder, fname, ftype, fsize, fdate);
			cout << "the file created." << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 2:
			cout << "folder name:";
			cin >> foldername;
			selectedFolder = searchfolder(root, foldername);
			if (!selectedFolder) {
				cout << "folder not found" << endl;
				break;
			}
			cout << "file name:";
			cin >> fname;
			deleteFile(selectedFolder, fname);
			cout << "file deleted" << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 3:
			cout << "folder name:";
			cin >> foldername;
			selectedFolder = searchfolder(root, foldername);
			if (!selectedFolder) {
				cout << "folder not found" << endl;
				break;
			}
			cout << "file name:";
			cin >> fname;
			q = searchfile(selectedFolder, fname);
			if (q != nullptr)
				cout << "file found:" << p << endl;
			else cout << "file didn't found" << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 4:
			cout << "folder name:";
			cin >> foldername;
			selectedFolder = searchfolder(root, foldername);
			if (!selectedFolder) {
				cout << "folder not found" << endl;
				break;
			}
			sortfiles(selectedFolder);
			cout << "Folder's files sorted" << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 5:
			cout << "folder name:";
			cin >> foldername;
			selectedFolder = searchfolder(root, foldername);
			if (!selectedFolder) {
				cout << "folder not found" << endl;
				break;
			}
			folderstotalsize(selectedFolder);
			cout << "\n*****************\n" << endl;
			break;
		case 6:
			cout << "folder name:";
			cin >> foldername;
			selectedFolder = searchfolder(root, foldername);
			if (!selectedFolder) {
				cout << "folder not found" << endl;
				break;
			}
			printFiles(selectedFolder);
			cout << "\n*****************\n" << endl;
			break;
		case 7:
			cout << "folder name:";
			cin >> foldername;
			p = searchfolder(root, foldername);
			if (p != nullptr)
				cout << "the folder found" << endl;
			else
				cout << "the folder didn't found" << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 8:
			x = depth(root);
			cout << "the depth is:" << x << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 9:
			cout << "enter the folder name:";
			cin >> foldername;
			selectedFolder = searchfolder(root, foldername);
			if (!selectedFolder) {
				cout << "folder not found" << endl;
				break;
			}
			cout << "the new folder's name:";
			cin >> fname;
			addfolder(selectedFolder, fname);
			cout << "the folder added." << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 10:
			cout << "enter the folder which you want to delete:";
			cin >> fname;
			deletefolder(root, fname);
			cout << "the folder deleted." << endl;
			cout << "\n******************\n" << endl;
			break;
		case 11:
			traversal(root);
			cout << "\n*****************\n" << endl;
			break;
		case 12:
			cout << "total folders:" << endl;
			cout << countFolder(root) << endl;
			cout << "\n*****************\n" << endl;
			break;
		case 0:
			cout << "exiting..";
			break;
		default:
			cout << "invalid choice!";
		}
	} while (choice != 0);
	cin.get();
	cin.ignore();
}