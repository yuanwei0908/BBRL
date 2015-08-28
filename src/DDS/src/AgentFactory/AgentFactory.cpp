
#include "AgentFactory.h"
#include "EGreedyAgentFactory.h"
#include "SoftMaxAgentFactory.h"
#include "VDBEEGreedyAgentFactory.h"
#include "FormulaAgentFactory.h"

using namespace utils;


// ===========================================================================
//	Public Constructors/Destructors
// ===========================================================================
dds::AgentFactory::~AgentFactory() {}


// ===========================================================================
//	Public static methods
// ===========================================================================
dds::AgentFactory* dds::AgentFactory::parse(int argc, char* argv[])
                                             throw (parsing::ParsingException)
{
     //   Get 'agentFactoryClassName'
     string agentFactoryClassName =
               utils::parsing::getValue(argc, argv, "--agent_factory");


     //   Get 'agentFactory'
     if (agentFactoryClassName == "EGreedyAgentFactory")
     {
          //   Get 'minEps' and 'maxEps'
          vector<string> tmp = parsing::getValues(argc, argv, "--epsilon", 2);
          double minEps = atof(tmp[0].c_str());
          double maxEps = atof(tmp[1].c_str());
          
          //   Return
          return new EGreedyAgentFactory(minEps, maxEps);
     }
     
     if (agentFactoryClassName == "SoftMaxAgentFactory")
     {
          //   Get 'minTau' and 'maxTau'
          vector<string> tmp = parsing::getValues(argc, argv, "--tau", 2);
          double minTau = atof(tmp[0].c_str());
          double maxTau = atof(tmp[1].c_str());
          
          //   Return
          return new SoftMaxAgentFactory(minTau, maxTau);
     }
     
     if (agentFactoryClassName == "VDBEEGreedyAgentFactory")
     {
          //   Get 'minSigma' and 'maxSigma'
          vector<string> tmp = parsing::getValues(argc, argv, "--sigma", 2);
          double minSigma = atof(tmp[0].c_str());
          double maxSigma = atof(tmp[1].c_str());
          
          //   Get 'minDelta' and 'maxDelta'
          tmp = parsing::getValues(argc, argv, "--delta", 2);
          double minDelta = atof(tmp[0].c_str());
          double maxDelta = atof(tmp[1].c_str());
          
          //   Get 'minEps' and 'maxEps'
          tmp = parsing::getValues(argc, argv, "--ini_epsilon", 2);
          double minIniEps = atof(tmp[0].c_str());
          double maxIniEps = atof(tmp[1].c_str());
          
          //   Return
          return new VDBEEGreedyAgentFactory(
                    minSigma, maxSigma, minDelta, maxDelta,
                    minIniEps, maxIniEps);
     }
     
     if (agentFactoryClassName == "FormulaAgentFactory")
     {
          //   Get 'minW', 'maxW' & 'accW'
          vector<string> tmp = parsing::getValues(argc, argv, "--weights", 2);
          double minW = atof(tmp[0].c_str());
          double maxW = atof(tmp[1].c_str());
          
          //   Get 'varNameList'
          string tmp2 = parsing::getValue(argc, argv, "--variables");
          unsigned int nVar = atoi(tmp2.c_str());
          
          vector<string> varNameList
                    = parsing::getValues(argc, argv, "--variables", (nVar + 1));                                              
          varNameList.erase(varNameList.begin());
          
          
          //   Return
          return new FormulaAgentFactory(minW, maxW, 0.01, varNameList);
     }
     
     throw parsing::ParsingException("--agent_factory");
}


// ===========================================================================
//	Public methods
// ===========================================================================
void dds::AgentFactory::serialize(ostream& os) const
{
	Serializable::serialize(os);
	
	
	os << AgentFactory::toString() << "\n";
	os << 0 << "\n";
}


void dds::AgentFactory::deserialize(istream& is) throw (SerializableException)
{
	Serializable::deserialize(is);
	
	string tmp;


	//	Class name check
	if (!getline(is, tmp)) { throwEOFMsg("class name"); }
	string className = tmp;
	if (className != AgentFactory::toString())
	{
		string msg = "Error with 'class name'.\n";
		throw SerializableException(msg);
	}
	
	
	//	Number of parameters
	if (!getline(is, tmp)) { throwEOFMsg("number of parameters"); }
	int n = atoi(tmp.c_str());

	int i = 0;
	
	
	//	Number of parameters check
	if (n != i)
	{
		string msg = "Error with 'number of parameters'.\n";
		throw SerializableException(msg);
	}
}