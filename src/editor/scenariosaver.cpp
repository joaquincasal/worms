#include "scenariosaver.h"
#include "yaml-cpp/yaml.h"
#include "draglabel.h"
#include "config.h"
#include <QList>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h> 

using std::string;
using std::vector;
using std::map;

int ScenarioSaver::save_scenario(QList<DragLabel*>& worms_labels, \
                            QList<DragLabel*>& beams_labels, string filename){
    if (check_intersections(worms_labels, beams_labels)){
        return 1;
    }
    if (worms_labels.empty()){
        return 2;
    }

    YAML::Emitter parser;
    parser << YAML::BeginMap;
    parser << YAML::Key << "scenario";
    parser << YAML::Value << data;

    parser << YAML::Key << "worms";
    parser << YAML::Value << YAML::BeginSeq;
    int id_counter = 1;
    int scenario_height = get_height();
    for (DragLabel* worm_label : worms_labels){
        float x = pixels_to_meters(worm_label->geometry().center().x());
        float y = pixels_to_meters(worm_label->geometry().center().y());
        y = y * -1 + scenario_height;
        std::map<string, string> worm;
        worm["id"] = std::to_string(id_counter);
        worm["x"] = std::to_string(x);
        worm["y"] = std::to_string(y);
        worm["image"] = worm_label->get_image_filename().toStdString();
        parser << worm;
        id_counter += 1;
    }
    parser << YAML::EndSeq;

    parser << YAML::Key << "beams";
    parser << YAML::Value << YAML::BeginSeq;
    id_counter = 1;
    for (DragLabel* beam_label : beams_labels){
        float x = pixels_to_meters(beam_label->geometry().center().x());
        float y = pixels_to_meters(beam_label->geometry().center().y());
        y = y * -1 + scenario_height;
        std::map<string, string> beam;
        beam["id"] = std::to_string(id_counter);
        beam["x"] = std::to_string(x);
        beam["y"] = std::to_string(y);
        beam["length"] = std::to_string(beam_label->get_width());
        beam["height"] = std::to_string(beam_label->get_height());
        beam["angle"] = std::to_string(beam_label->get_angle());
        beam["image"] = beam_label->get_image_filename().toStdString();
        parser << beam;
        id_counter += 1;
    }
    parser << YAML::EndSeq << YAML::EndMap;

    std::ofstream fout(filename);
    fout << parser.c_str();
    return 0;
}

void ScenarioSaver::load_scenario(string filename, int& scenario_height,\
                        int& scenario_width, string& background,\
                        vector<map<string, string>>& worms,\
                        vector<map<string, string>>& beams){
    YAML::Node new_scenario = YAML::LoadFile(filename);

    data = new_scenario["scenario"].as<map<string, string>>();
    scenario_height = get_height();
    scenario_width = get_width();
    background = get_background();

    vector<map<string, string>> scenario_worms = new_scenario["worms"].\
                                              as<vector<map<string, string>>>();
    vector<map<string, string>> scenario_beams = new_scenario["beams"].\
                                              as<vector<map<string, string>>>();

    for (map<string, string> worm : scenario_worms){
        map<string, string> new_worm;
        float x = std::stof(worm.at("x")) - WORM_SIZE / 2;
        float y = std::stof(worm.at("y")) + WORM_SIZE / 2;
        x = meters_to_pixels(x);
        y = meters_to_pixels((y - scenario_height) * -1);
        string image = worm.at("image");

        new_worm["x"] = std::to_string(x);
        new_worm["y"] = std::to_string(y);
        new_worm["image"] = image;
        worms.push_back(new_worm);
    }

    for (map<string, string> beam : scenario_beams){
        map<string, string> new_beam;
        float x = std::stof(beam.at("x"));
        float y = std::stof(beam.at("y"));
        int length = std::stoi(beam.at("length"));
        int height = std::stoi(beam.at("height"));
        int angle = std::stoi(beam.at("angle"));
        if (angle == 0){
            x -= length / 2;
            y += height / 2;
        } else if (angle == 45 || angle == 135){
            double square_side = get_side(length);
            x -= square_side / 2;
            y += square_side / 2;
        } else if (angle == 90){
            x -= height / 2;
            y += length / 2;
        }
        x = meters_to_pixels(x);
        y = meters_to_pixels((y - scenario_height) * -1);
        string image = beam.at("image");

        new_beam["x"] = std::to_string(x);
        new_beam["y"] = std::to_string(y);
        new_beam["length"] = std::to_string(length);
        new_beam["height"] = std::to_string(height);
        new_beam["angle"] = std::to_string(angle);
        new_beam["image"] = image;
        beams.push_back(new_beam);
    }
}

float ScenarioSaver::pixels_to_meters(float pixels)
{
    return pixels / PIXEL_METER_CONVERSION;
}

float ScenarioSaver::meters_to_pixels(float meters)
{
    return meters * PIXEL_METER_CONVERSION;
}

bool ScenarioSaver::check_intersections(QList<DragLabel*>& worms_labels,\
                                        QList<DragLabel*>& beams_labels){
    QList<DragLabel*> labels = worms_labels;
    labels.append(beams_labels);
    for (DragLabel* label : labels){
        for (DragLabel* other_label : labels){
            if (label == other_label){
                continue;
            }
            if (label->geometry().intersects(other_label->geometry())){
                return true;
            }
        }
    }
    return false;
}

void ScenarioSaver::set_size(int width, int height){
    data["width"] = std::to_string(width);
    data["height"] = std::to_string(height);
}

void ScenarioSaver::set_background(string filename){
    data["background"] = filename;
}

int ScenarioSaver::get_width(){
    return std::stoi(data.at("width"));
}

int ScenarioSaver::get_height(){
    return std::stoi(data.at("height"));
}

string ScenarioSaver::get_background(){
    return data.at("background");
}

double ScenarioSaver::get_side(double diagonal){
    return sqrt((diagonal * diagonal) / 2);
}
