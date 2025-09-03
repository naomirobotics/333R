#include "main.h"
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/core/lv_obj_scroll.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/core/lv_obj_tree.h"
#include "liblvgl/extra/widgets/list/lv_list.h"
#include "liblvgl/extra/widgets/spinbox/lv_spinbox.h"
#include "liblvgl/extra/widgets/tabview/lv_tabview.h"
#include "liblvgl/font/lv_font.h"
#include "liblvgl/misc/lv_anim.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/misc/lv_color.h"
#include "liblvgl/misc/lv_style.h"
#include "liblvgl/widgets/lv_btn.h"
#include "liblvgl/widgets/lv_btnmatrix.h"
#include "liblvgl/widgets/lv_label.h"
#include "liblvgl/widgets/lv_roller.h"
#include "liblvgl/widgets/lv_switch.h"
#include "pros/colors.hpp"
#include "pros/rtos.hpp"
#include <cstddef>
#include <string>
#include <vector>


bool StatsOn = false;


using namespace robos;

std::string Line0 = "";

std::string Line1 = "";

std::string Line2 = "";

std::string Line3 = "";

std::string Line4 = "";

std::string Line5 = "";

std::string Main = "";

int CurrentAuton = 0;

int MaxAutos;

std::vector<AutonCallbacks> Autonomi = {};




void Selector::init(){

    lv_style_t Style1;

    lv_style_init(&Style1);

    RobosTabs = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 40);

    Console = lv_tabview_add_tab(RobosTabs, "Console");

    SelectorTab = lv_tabview_add_tab(RobosTabs, "Selector");

    PrintLines = lv_label_create(Console);

    AutonSelector = lv_roller_create(SelectorTab);

    ColorSelector = lv_roller_create(SelectorTab);

    lv_roller_set_options(AutonSelector, "None", LV_ROLLER_MODE_NORMAL);

    lv_roller_set_options(ColorSelector, "Red\nBlue", LV_ROLLER_MODE_NORMAL);

    lv_roller_set_visible_row_count(ColorSelector, 3);

    Main = Line0 + "\n\n" + Line1 + "\n\n" + Line2 + "\n\n" + Line3 + "\n\n" + Line4 + "\n\n" + Line5;

    lv_obj_set_size(AutonSelector, 250, 220);

    lv_obj_set_pos(AutonSelector, 80, 30);

    lv_obj_set_scrollbar_mode(RobosTabs, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_scrollbar_mode(Console, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_scrollbar_mode(SelectorTab, LV_SCROLLBAR_MODE_OFF);

    lv_label_set_text(PrintLines, Main.c_str());

    lv_obj_set_style_radius(AutonSelector, 20, LV_ANIM_OFF);

    lv_obj_set_style_radius(ColorSelector, 20, LV_ANIM_OFF);

    lv_roller_set_visible_row_count(AutonSelector, 3);

    lv_obj_set_size(ColorSelector, 0,0);

    lv_obj_set_pos(ColorSelector, 200, 30);

    lv_obj_set_style_text_font(AutonSelector,&lv_font_montserrat_24, LV_ANIM_OFF);

    lv_obj_set_style_text_font(ColorSelector,&lv_font_montserrat_24,LV_ANIM_OFF);

    lv_obj_set_style_border_color(RobosTabs, lv_color_make(255, 0, 0), LV_ANIM_OFF);

    lv_obj_set_style_border_color(AutonSelector, lv_color_make(255, 0, 0), LV_ANIM_OFF);

}

void Selector::Print(int line, std::string Text){

    switch (line) {

        case 0:

        Line0 = Text;

        break;

        case 1:

        Line1 = Text;

        break;

        case 2:

        Line2 = Text;

        break;

        case 3:

        Line3 = Text;

        break;

        case 4:

        Line4 = Text;

        break;

        case 5:

        Line5 = Text;

        break;

    }

    Main = Line0 + "\n\n" + Line1 + "\n\n" + Line2 + "\n\n" + Line3 + "\n\n" + Line4 + "\n\n" + Line5;

    lv_label_set_text(PrintLines, Main.c_str());

}

void Selector::SetAutons(std::vector<AutonCallbacks> Callbacks){

    Autonomi = Callbacks;

    MaxAutos = Autonomi.size();

    std::string options = "";

    for (int i = 0; i < MaxAutos; i++) {

        options += Autonomi[i].Names;

        
        if (i != MaxAutos - 1) {

             options += "\n";

        }
       
    
    }

    lv_roller_set_options(AutonSelector,options.c_str(), LV_ROLLER_MODE_NORMAL);


}

void Selector::RunAuton(){

    CurrentAuton = lv_roller_get_selected(AutonSelector);

    Autonomi[CurrentAuton].Auto();

}

int Selector::GetColor(){

    return lv_roller_get_selected(ColorSelector);

}





