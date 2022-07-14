extern std::string printLanguage;

std::string outsideLimitMsg;
std::string lowerLimitWarning;
std::string upperLimitWarning;

void printPhrase() {

        if(printLanguage == "GERMAN") {
            outsideLimitMsg = " Außerhalb der Grenzen";
            lowerLimitWarning = " ACHTUNG: Annäherung an die untere Grenze für ";
            upperLimitWarning = " ACHTUNG: Annäherung an die Obergrenze für ";    
        }
        else {
            outsideLimitMsg = " Outside the limits";
            lowerLimitWarning = " WARNING: Approaching the lower limit for ";
            upperLimitWarning = " WARNING: Approaching the upper limit for ";
        }
}