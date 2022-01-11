#include <iostream>
#include <vector>
#include <ctime>

class Branch {
    Branch *bigBranch;
    std::string name;
public:
    Branch(std::string inName, Branch *inBigBranch = nullptr) : name(inName), bigBranch(inBigBranch) {
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

};

class Tree {
    std::vector<Branch *> branches;
public:
    Tree() {}

    Branch *addBranch(std::string name, Branch *parent = nullptr) {
        Branch *branch = new Branch(name, parent);
        branches.push_back(branch);
        return branch;
    }

    int findElf(std::string name) {
        for (int i = 0; i < branches.size(); ++i) {
            Branch *elf = branches[i]->findElf(name);
            if (elf != nullptr) {
                std::cout << "The elf " << name << " has " << countNeighboursOnBigBranch(elf) << std::endl;
            }else{
                std::cout << "The elf not found"<< std::endl;
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
    std::vector<Tree *> trees;
    std::srand(time(nullptr));

    for (int i = 0; i < 5; ++i) {
        int BranchGigCount = 0;
        int BranchMiddleCount = 0;

        Tree *tree = new Tree();
        trees.push_back(tree);
        BranchGigCount = (std::rand() % 3) + 3;
        for (int j = 0; j < BranchGigCount; ++j) {
            std::cout << "Tree #" << i << " big #" << j << " middle #0" << std::endl;
            std::cout << "Input name of the elf: ";
            std::cin >> elfName;
            Branch *branchBig = tree->addBranch(elfName);

            BranchMiddleCount = (std::rand() % 2) + 2;
            for (int k = 0; k < BranchMiddleCount; ++k) {
                std::cout << "Tree #" << i << " big #" << j << " middle #" << k << std::endl;
                std::cout << "Input name of the elf: ";
                std::cin >> elfName;
                tree->addBranch(elfName, branchBig);
            }
        }

    }
    std::cout << std::endl << "=======================================";
    std::cout << std::endl << "Counting elf's neighbors.";
    std::cout << "Input name of the elf: ";
    std::cin >> elfName;

    for (int i = 0; i < trees.size(); ++i) {
        trees[i]->findElf(elfName);
    }

    return 0;
}
