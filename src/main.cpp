#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>


const std::string config_file_path = "../config/spectrum/spectrogram.conf";
const std::string audio_file_path = "../data/audio/";
const std::string csv_export_path = "../data/extracted/";

std::string get_name(const std::filesystem::directory_entry& dir)
{
    auto name = dir.path().string().substr(audio_file_path.length());
    name.erase(name.end() - 4, name.end());
    return name;
}

std::vector<std::string> get_file_list()
{
    namespace fs = std::filesystem;
    
    auto counting_it = std::next(fs::directory_iterator(audio_file_path));
    const size_t file_count = std::distance(fs::begin(counting_it), fs::end(counting_it));

    auto file_path_it = std::next(fs::directory_iterator(audio_file_path));
    std::vector<std::string> file_names;
    file_names.reserve(file_count);

    for (const auto& file : file_path_it)
        file_names.emplace_back(get_name(file));

    return file_names;
}

void extract_features(
    const std::string& config_path,
    const std::string& song_path,
    const std::string& export_path
)
{
    auto output_name = audio_file_path;
    output_name.erase(output_name.begin(), output_name.begin() + 14);
    output_name.erase(output_name.end() - 4, output_name.end());

    std::ostringstream cmd;
    cmd << "../bin/SMILExtract -C " << config_path
        << " -I " << song_path
        << " -csvoutput " << export_path
        << " -instname " << output_name;

    int ret = std::system(cmd.str().c_str());
}

int main()
{
    auto names = get_file_list();

    for (const auto& n : names)
    {
        int x;
    }
}