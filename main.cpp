#include <iostream>
#include <vector>
#include <ctime>

class Branch {
    int id;
    std::string name;
    Branch *bigBranch = nullptr;
public:

    Branch(std::string inName, Branch *inBigBranch, int inId) : name(inName), bigBranch(inBigBranch), id(inId) {
        if (inBigBranch == nullptr) {
            bigBranch = this;
        }
    }

    Branch *findElf(std::string inName) {

        if (inName == "None") return nullptr;

        if (inName == name) {
            return this;
        } else {
            return nullptr;
        }
    }

    int getResident() {
        if (name == "None") {
            return 0;
        } else {
            return 1;
        }
    }

    Branch *getBigBranch() {
        return bigBranch;
    }

    int getId() {
        return id;
    }

};

class Tree {
    std::vector<Branch *> branches;
public:
    ~Tree() {
        for (int i = 0; i < branches.size(); ++i) {
            delete branches[i];
        }
    }

    Branch *addBranch(std::string name, Branch *parent, int inId) {
        Branch *branch = new Branch(name, parent, inId);
        branches.push_back(branch);
        return branch;
    }

    void findElf(std::string name, int idTree) {

        for (int i = 0; i < branches.size(); ++i) {
            Branch *elf = branches[i]->findElf(name);
            if (elf != nullptr) {

                std::cout << "The elf " << name << " found on the tree #" << idTree << " branch #" << elf->getId()
                          << ". Hi has " << countNeighboursOnBigBranch(elf) << std::endl;
            }
        }
    }

    int countNeighboursOnBigBranch(Branch *elf) {
        Branch *bigBranch = elf->getBigBranch();
        int neighbours = 0;
        for (int i = 0; i < branches.size(); ++i) {
            if (branches[i]->getBigBranch() == bigBranch && branches[i] != elf) {
                neighbours += branches[i]->getResident();
            }
        }
        return neighbours;
    }
};

int main() {

    std::string elfName;
    Tree *trees[5] = {nullptr};
    std::srand(time(nullptr));

    for (int i = 0; i < 5; ++i) {
        int BranchBigCount = 0;
        int BranchMiddleCount = 0;

        int idBranch = 0;
        trees[i] = new Tree();
        BranchBigCount = (std::rand() % 3) + 3;
        for (int j = 0; j < BranchBigCount; ++j) {
            std::cout << "Tree #" << i << " branch #" << idBranch << " (big). Input name of the elf: ";
            std::cin >> elfName;
            Branch *branchBig = trees[i]->addBranch(elfName, nullptr, idBranch);
            idBranch++;
            BranchMiddleCount = (std::rand() % 2) + 2;
            for (int k = 0; k < BranchMiddleCount; ++k) {
                std::cout << "Tree #" << i << " branch #" << idBranch << " (middle). Input name of the elf: ";
                std::cin >> elfName;
                trees[i]->addBranch(elfName, branchBig, idBranch);
                idBranch++;
            }
        }
        std::cout << std::endl << "=================== Tree #" << i << " is full ====================" << std::endl;
    }
    std::cout << std::endl << "=======================================";
    std::cout << std::endl << "Counting elf's neighbors.";
    std::cout << "Input name of the elf: ";
    std::cin >> elfName;

    for (int i = 0; i < 5; ++i) {
        trees[i]->findElf(elfName, i);

        delete trees[i];
        trees[i] = nullptr;
    }


    return 0;
}
