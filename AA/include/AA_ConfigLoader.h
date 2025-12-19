#include <string>

class AA_ConfigLoader
{
    private:

        std::string config_data = "";

    public:

        AA_ConfigLoader() = default;
        ~AA_ConfigLoader() = default;
        void SetConfigFile(std::string p_config_file_path);
        std::string GetField(std::string field);
};