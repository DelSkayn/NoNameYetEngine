#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <map>

struct ProfileTime{
    double totalTime;
    unsigned int timesProfiled;
    std::string name;
};

class ProfileSample{
    public:
        ProfileSample(std::string name);
        ~ProfileSample();
    private:
        unsigned int profileIndex;
        double startTime;
        std::string name;
};

class Profile{
    friend class ProfileSample;
    public:
        static std::string getProfileAsString();
        static void reset();
    private:
        static std::map<std::string,ProfileTime> profileList;
        static unsigned int currentProfile;
};

#define VALUE( arg ) #arg
#define STR_CONCAT(arg , arg2) arg ## arg2
#define STR_CONCAT_UPPER(x,y) STR_CONCAT(x,y)

#define PROFILE(name) ProfileSample STR_CONCAT_UPPER(name,_profile)(VALUE(name));


#endif /* PROFILE_H */
