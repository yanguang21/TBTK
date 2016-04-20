/** @file AmplitudeSet.cpp
 *
 *  @author Kristofer Björnson
 */

#include "../include/AmplitudeSet.h"
#include <iostream>

using namespace std;

namespace TBTK{

void AmplitudeSet::print(){
	tree.print();
}

AmplitudeSet::Iterator AmplitudeSet::getIterator(){
	return AmplitudeSet::Iterator(&tree);
}

AmplitudeSet::Iterator::Iterator(TreeNode* tree){
	it = new TreeNode::Iterator(tree);
}

AmplitudeSet::Iterator::~Iterator(){
	delete it;
}

void AmplitudeSet::Iterator::reset(){
	it->reset();
}

void AmplitudeSet::Iterator::searchNextHA(){
	it->searchNextHA();
}

HoppingAmplitude* AmplitudeSet::Iterator::getHA(){
	return it->getHA();
}

void AmplitudeSet::tabulate(int **table, int *dims){
	Iterator it = getIterator();
	HoppingAmplitude *ha;
	int numHA = 0;
	int maxIndexSize = 0;
	while((ha = it.getHA())){
		numHA++;

		int indexSize = ha->fromIndex.indices.size();
		if(indexSize > maxIndexSize)
			maxIndexSize = indexSize;

		it.searchNextHA();
	}

	dims[0] = numHA;
	dims[1] = 2*maxIndexSize;
	(*table) = new int[dims[0]*dims[1]];
	for(int n = 0; n < dims[0]*dims[1]; n++)
		(*table)[n] = -1;

	it.reset();
	int counter = 0;
	while((ha = it.getHA())){
		for(unsigned int n = 0; n < ha->fromIndex.indices.size(); n++)
			(*table)[dims[1]*counter+n] = ha->fromIndex.indices.at(n);
		for(unsigned int n = 0; n < ha->toIndex.indices.size(); n++)
			(*table)[dims[1]*counter+n+dims[1]/2] = ha->toIndex.indices.at(n);
		it.searchNextHA();
		counter++;
	}
}

};	//End of namespace TBTK
