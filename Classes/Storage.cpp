#include "Storage.h"

void Storage::tankStore(tank obj)
{
	tankStorage.push_back(obj);
}

void Storage::tankRemove(tank* ptr)
{
	for (vector<tank>::iterator it = tankStorage.begin(); it != tankStorage.end(); it++) {
		if (it->storageNum == ptr->storageNum) {
			tankStorage.erase(it);
			break;
		}
	}
}

void Storage::mageStore(mage obj)
{
	mageStorage.push_back(obj);
}

void Storage::mageRemove(mage* ptr)
{
	for (vector<mage>::iterator it = mageStorage.begin(); it != mageStorage.end(); it++) {
		if (it->storageNum == ptr->storageNum) {
			mageStorage.erase(it);
			break;
		}
	}
}

void Storage::shooterStore(shooter obj)
{
	shooterStorage.push_back(obj);
}

void Storage::shooterRemove(shooter* ptr)
{
	for (vector<shooter>::iterator it = shooterStorage.begin(); it != shooterStorage.end(); it++) {
		if (it->storageNum == ptr->storageNum) {
			shooterStorage.erase(it);
			break;
		}
	}
}

void Storage::stalkerStore(stalker obj)
{
	stalkerStorage.push_back(obj);
}

void Storage::stalkerRemove(stalker* ptr)
{
	for (vector<stalker>::iterator it = stalkerStorage.begin(); it != stalkerStorage.end(); it++) {
		if (it->storageNum == ptr->storageNum) {
			stalkerStorage.erase(it);
			break;
		}
	}
}


void Storage::therapistStore(therapist obj)
{
	therapistStorage.push_back(obj);
}

void Storage::therapistRemove(therapist* ptr)
{
	for (vector<therapist>::iterator it = therapistStorage.begin(); it != therapistStorage.end(); it++) {
		if (it->storageNum == ptr->storageNum) {
			therapistStorage.erase(it);
			break;
		}
	}
}
