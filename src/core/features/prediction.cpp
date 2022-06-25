#include "features.hpp"
// Credit: AimTux/Fuzion



void c_engine_prediction::store_some_data()
{
    const auto active_weapon = g_sdk.m_local->get_active_weapon();

    if (!active_weapon)
        return;

    m_backup_data.m_spread = g_sdk.m_active_weapon->get_spread();
    m_backup_data.m_accuracy = g_sdk.m_active_weapon->get_accuracy_penatly();
    m_backup_data.m_current_time = g_interfaces.m_globals->m_current_time;
    m_backup_data.m_frame_time = g_interfaces.m_globals->m_frame_time;

    if (this->m_random_seed == 0 || !this->m_predicted_player)
    {
        this->m_random_seed = g_sdk.m_random_seed_sig;
        this->m_predicted_player = g_sdk.m_predicted_player_sig;
    }
}

void c_engine_prediction::update()
{
    if (g_sdk.m_fsn_stage != frame_net_update_end)
        return;

    return g_interfaces.m_prediction->update(g_interfaces.m_client_state->m_delta_tick,
                                                     g_interfaces.m_client_state->m_delta_tick > 0,
                                                     g_interfaces.m_client_state->m_last_command_ack,
                                                     g_interfaces.m_client_state->m_choked_commands + g_interfaces.m_client_state->m_last_outgoing_command);
}


void c_engine_prediction::start()
{
    const auto active_weapon = g_sdk.m_local->get_active_weapon();
    if (!g_sdk.m_active_weapon)
        return;

    const auto weapon_data = active_weapon->get_weapon_data();
    if (!weapon_data)
        return;

    **reinterpret_cast<c_base_player***>(this->m_prediction_player) = g_sdk.m_local;
    **reinterpret_cast<int**>(this->m_random_seed) = c_packet_manager::get()->get_command()->m_random_seed;

    g_interfaces.m_globals->m_current_time = TICKS_TO_TIME(g_sdk.m_local->get_tickbase());
    g_interfaces.m_globals->m_frame_time = g_interfaces.m_globals->m_intervalpertick;

    const auto backup_in_prediction = g_intefaces.m_prediction->m_in_prediction;
    const auto backup_time_predicted = g_intefaces.m_prediction->m_first_time_predicted;

    g_intefaces.m_prediction->m_in_prediction = true;
    g_intefaces.m_prediction->m_first_time_predicted = false;

    g_interfaces.m_move_helper->set_host(g_sdk.m_local);
    g_interfaces.m_game_movement->start_track_prediction_errors(g_sdk.m_local);
    g_interfaces.m_prediction->setup_move(g_sdk.m_local, c_packet_manager::get()->get_command(),
                                         g_interfaces.m_move_helper, &m_move_data);
    g_interfaces.m_game_movement->process_movement(g_sdk.m_local, &m_move_data);

    g_interfaces.m_prediction->finish_move(g_sdk.m_local, c_packet_manager::get()->get_command(), &m_move_data);
    g_interfaces.m_game_movement->finish_track_prediction_errors(g_sdk.m_local);
    g_interfaces.m_move_helper->set_host(nullptr);

    active_weapon->update_accuracy_penalty();

    float final_calc_innacuracy{};
    const auto is_sniper_weapon = (
        active_weapon->get_idx() == idx_t::weapon_awp
        || active_weapon->get_idx() == idx_t::weapon_g3sg1
        || active_weapon->get_idx() == idx_t::weapon_scar20
        || active_weapon->get_idx() == idx_t::ssg_008
    );

    g_sdk.m_accuracy_data->m_calculated_innacuracy = 0.0f;
    if (g_sdk.m_local->get_flags() & fl_ducking)
    {
        if ( is_sniper_weapon )
            final_calc_innacuracy = weapon_data->m_inaccuracy_crouch_alt;
        else
            final_calc_innacuracy = weapon_data->m_inaccuracy_crouch;
    }
    else if (is_sniper_weapon)
    {
          final_calc_innacuracy = weapon_data->m_inaccuracy_stand_alt;
    }
    else
    {
        final_calc_innacuracy = weapon_data->m_inaccuracy_stand;
    }
    g_sdk.m_accuracy_data->m_calculated_innacuracy = final_calc_innacuracy;

    g_intefaces.m_prediction->m_in_prediction = backup_in_prediction;
    g_intefaces.m_prediction->m_first_time_predicted = backup_time_predicted;
}

void c_engine_prediction::restore()
{
    auto active_weapon = g_sdk.m_local->get_active_weapon();

    if (!active_weapon)
        return;

    **reinterpret_cast<c_base_player***>(this->m_prediction_player) = nullptr;
    **reinterpret_cast<int**>(this->m_random_seed) = -1;

    active_weapon->get_spread() = m_backup_data.m_spread;
    active_weapon->get_accuracy_penatly() = m_backup_data.m_accuracy;

    g_interfaces.m_globals->m_current_time = m_backup_data.m_current_time;
    g_interfaces.m_globals->m_frame_time = m_backup_data.m_frame_time;
}

void __stdcall c_hooks::hk_create_move(int sequence, float frametime, bool is_active, bool& send_packet)
{
    c_engine_prediction::get()->update();
    c_engine_prediction::get()->store_some_data();
    c_engine_prediction::get()->start();
    {
     
    }
    c_engine_prediction::get()->restore();
}
