#include<iostream>
#include<vector>
class Functor{
private:
	bool doneState;
protected:
	int resultValue;
	std::vector <Functor*> subFunctors;
	virtual void run()=0;
public:
	Functor(){
		doneState=false;
		resultValue=0;
	}
	void checkSubsAndDoYourFunction(){
		for(int i=0;i<subFunctors.size();i++){
			if(!subFunctors[i]->isItDone()){
				subFunctors[i]->checkSubsAndDoYourFunction();
				return;
			}
		}
		this->run();
		doneState=true;
	}
	bool isItDone(){
		return doneState;
	}
	int getResult(){
		return resultValue;
	}
	void resetYourSelfAndSubs(){
		for(int i=0;i<subFunctors.size();i++){
			subFunctors[i]->resetYourSelfAndSubs();
		}
		doneState=false;
	}
};
class Functor_cin:public Functor{
private:
	void run(){
		std::cin>>resultValue;
	}
};
class Functor_cout:public Functor{
private:
	void run(){
		if(subFunctors.size()==1){
			std::cout<<subFunctors[0]->getResult();
		}else throw -1;
	}
};
class Functor_neg:public Functor{
private:
	void run(){
		if(subFunctors.size()==1){
			resultValue=-subFunctors[0]->getResult();
		}else throw -1;
	}
};
class Functor_add:public Functor{
private:
	void run(){
		if(subFunctors.size()==2){
			resultValue=subFunctors[0]->getResult()+subFunctors[1]->getResult();
		}else throw -1;
	}
};
class Functor_mul:public Functor{
private:
	void run(){
		if(subFunctors.size()==2){
			resultValue=subFunctors[0]->getResult()*subFunctors[1]->getResult();
		}else throw -1;
	}
};
class Functor_if:public Functor{
private:
	void run(){
		if(subFunctors.size()==3){
			resultValue=subFunctors[0]->getResult()?subFunctors[1]->getResult():subFunctors[2]->getResult();
		}else throw -1;
	}
};