#include "Storage.h"

void Storage::tankStore(tank* obj)
{
	tankStorage.pushBack(obj);
}

void Storage::tankRemove(tank* ptr)
{
	for (Vector<tank*>::iterator it = tankStorage.begin(); it != tankStorage.end(); it++) {
		if ((*it)->storageNum == ptr->storageNum) {
			tankStorage.erase(it);
			break;
		}
	}
}

void Storage::mageStore(mage* obj)
{
	mageStorage.pushBack(obj);
}

void Storage::mageRemove(mage* ptr)
{
	for (Vector<mage*>::iterator it = mageStorage.begin(); it != mageStorage.end(); it++) {
		if ((*it)->storageNum == ptr->storageNum) {
			mageStorage.erase(it);
			break;
		}
	}
}

void Storage::shooterStore(shooter* obj)
{
	shooterStorage.pushBack(obj);
}

void Storage::shooterRemove(shooter* ptr)
{
	for (Vector<shooter*>::iterator it = shooterStorage.begin(); it != shooterStorage.end(); it++) {
		if ((*it)->storageNum == ptr->storageNum) {
			shooterStorage.erase(it);
			break;
		}
	}
}

void Storage::stalkerStore(stalker* obj)
{
	stalkerStorage.pushBack(obj);
}

void Storage::stalkerRemove(stalker* ptr)
{
	for (Vector<stalker*>::iterator it = stalkerStorage.begin(); it != stalkerStorage.end(); it++) {
		if ((*it)->storageNum == ptr->storageNum) {
			stalkerStorage.erase(it);
			break;
		}
	}
}


void Storage::therapistStore(therapist* obj)
{
	therapistStorage.pushBack(obj);
}

void Storage::therapistRemove(therapist* ptr)
{
	for (Vector<therapist*>::iterator it = therapistStorage.begin(); it != therapistStorage.end(); it++) {
		if ((*it)->storageNum == ptr->storageNum) {
			therapistStorage.erase(it);
			break;
		}
	}
}
