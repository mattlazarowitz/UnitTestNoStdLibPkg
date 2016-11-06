//#include <stdio.h>
//#include <stdlib.h> //All these are C standard library includes that cannot be used here
//#include <string.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include "person.h"

PersonRef Person_alloc(void)
{
	return (PersonRef)AllocatePool(sizeof(Person));
}

PersonRef Person_init(PersonRef self)
{
	return Person_initWithName(self, NULL);
}

PersonRef Person_initWithName(PersonRef self,char *fullname)
{
	self->fullname = NULL;
	self->firstname = NULL;
	self->lastname = NULL;
	Person_setFullName(self,fullname);
	return self;
}

PersonRef Person_personWithName(char *fullname)
{
	return Person_initWithName(Person_alloc(),fullname);
}

void Person_dealloc(PersonRef self)
{
	if (self) {
		gBS->FreePool(self->fullname);
		gBS->FreePool(self->firstname);
		gBS->FreePool(self->lastname);
		gBS->FreePool(self);
	}
}

static void setfullname(PersonRef self,char *fullname)
{
	gBS->FreePool(self->fullname);
	self->fullname = NULL;
	if (fullname) {
		self->fullname = (char*)AllocatePool(AsciiStrLen(fullname)+1);
		AsciiStrCpy(self->fullname,fullname);
	}
}

static void setfirstname(PersonRef self,char *firstname)
{
	gBS->FreePool(self->firstname);
	self->firstname = NULL;
	if (firstname) {
		self->firstname = (char*)AllocatePool(AsciiStrLen(firstname)+1);
		AsciiStrCpy(self->firstname,firstname);
	}
}

static void setlastname(PersonRef self,char *lastname)
{
	gBS->FreePool(self->lastname);
	self->lastname = NULL;
	if (lastname) {
		self->lastname = (char*)AllocatePool(AsciiStrLen(lastname)+1);
		AsciiStrCpy(self->lastname,lastname);
	}
}

static void makefullname(PersonRef self)
{
	size_t fl,ll,fulllen,pos;
	fl = ll = fulllen = pos = 0;
	if (self->firstname) {
		fl = AsciiStrLen(self->firstname);
	}
	if (self->lastname) {
		ll = AsciiStrLen(self->lastname);
	}
	if (fl) {
		fulllen = fl + 1;	/* + space */
	}
	if (ll) {
		fulllen = fulllen + ll + 1;	/* + null */
	}
	if (fulllen) {
		self->fullname = (char*)AllocatePool(fulllen);
		if (fl && ll) {
			//sprintf(self->fullname,"%a %a",self->firstname,self->lastname);
			AsciiSPrint(self->fullname,fulllen,"%a %a",self->firstname,self->lastname);
		} else {
			if (fl) {
				AsciiStrCpy(self->fullname,self->firstname);
			}
			if (ll) {
				AsciiStrCpy(self->fullname,self->lastname);
			}
		}
	}
}

static void makefirstname(PersonRef self)
{
	if (self->fullname) {
		char *p;
		int len;
		p = AsciiStrStr(self->fullname, " ");
		if (p) {
			len = (int)(p - self->fullname);
			p = (char*)AllocatePool(len + 1);
			AsciiStrnCpy(p,self->fullname,len);
			p[len] = '\0';
			setfirstname(self,p);
			gBS->FreePool(p);
		} else {
			setfirstname(self,self->fullname);
		}
	}
}

static void makelastname(PersonRef self)
{
	if (self->fullname) {
		char *p = AsciiStrStr(self->fullname, " ");
		if (p) {
			setlastname(self,p+1);
		} else {
			setlastname(self,"");
		}
	}
}

char* Person_fullName(PersonRef self)
{
	if (self->fullname == NULL) {
		makefullname(self);
	}
	return self->fullname;
}

char* Person_firstName(PersonRef self)
{
	if (self->firstname == NULL) {
		makefirstname(self);
	}
	return self->firstname;
}

char* Person_lastName(PersonRef self)
{
	if (self->lastname == NULL) {
		makelastname(self);
	}
	return self->lastname;
}

void Person_setFullName(PersonRef self,char *fullname)
{
	setfullname(self,fullname);
	setfirstname(self,NULL);
	setlastname(self,NULL);
}

void Person_setFirstName(PersonRef self,char *firstname)
{
	if (self->lastname == NULL) {
		makelastname(self);
	}
	setfirstname(self,firstname);
	setfullname(self,NULL);
}

void Person_setLastName(PersonRef self,char *lastname)
{
	if (self->firstname == NULL) {
		makefirstname(self);
	}
	setlastname(self,lastname);
	setfullname(self,NULL);
}
