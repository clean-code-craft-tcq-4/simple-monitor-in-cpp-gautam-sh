extern std::string printLanguage;

std::string outsideLimitMsg = " Outside the limits for ";
std::string lowerLimitWarning = " WARNING: Approaching the lower limit for ";
std::string upperLimitWarning = " WARNING: Approaching the upper limit for ";
std::string normalMsg = " Normal for ";

void printPhrase() {

        if(printLanguage == "GERMAN") {
            outsideLimitMsg = " Außerhalb der Grenzen für ";
            lowerLimitWarning = " ACHTUNG: Annäherung an die untere Grenze für ";
            upperLimitWarning = " ACHTUNG: Annäherung an die Obergrenze für "; 
            normalMsg = " Normal für "; 
        }
}