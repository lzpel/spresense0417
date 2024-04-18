
#include <nuttx/config.h>
#include <stdio.h>
#include <arch/board/board.h>
#include <arch/chip/audio.h>
#include "generator.h"

static bool app_power_on(void)
{
    /* Enable I2S pin. */

    cxd56_audio_en_i2s_io();

    /* Enable speaker output. */

    cxd56_audio_set_spout(true);

    /* Power on Audio driver */

    if (cxd56_audio_poweron() != CXD56_AUDIO_ECODE_OK)
    {
        return false;
    }

    /* Enable BaseBand driver output */

    if (cxd56_audio_en_output() != CXD56_AUDIO_ECODE_OK)
    {
        return false;
    }

    return true;
}

static bool app_power_off(void)
{
    /* Disable speaker output. */

    cxd56_audio_set_spout(false);

    /* Disable I2S pin. */

    cxd56_audio_dis_i2s_io();

    /* Power off Audio driver */

    if (cxd56_audio_dis_output() != CXD56_AUDIO_ECODE_OK)
    {
        return false;
    }

    /* Disable BaseBand driver output */

    if (cxd56_audio_poweroff() != CXD56_AUDIO_ECODE_OK)
    {
        return false;
    }

    return true;
}

static bool app_beep(bool en, int16_t vol, uint16_t freq)
{
    if (!en)
    {
        /* Stop beep */

        if (cxd56_audio_stop_beep() != CXD56_AUDIO_ECODE_OK)
        {
            return false;
        }
    }

    if (0 != freq)
    {
        /* Set beep frequency parameter */

        if (cxd56_audio_set_beep_freq(freq) != CXD56_AUDIO_ECODE_OK)
        {
            return false;
        }
    }

    if (255 != vol)
    {
        /* Set beep volume parameter */

        if (cxd56_audio_set_beep_vol(vol) != CXD56_AUDIO_ECODE_OK)
        {
            return false;
        }
    }

    if (en)
    {
        /* Play beep */

        if (cxd56_audio_play_beep() != CXD56_AUDIO_ECODE_OK)
        {
            return false;
        }
    }

    return true;
}
int main(int argc, FAR char *argv[]) { /* Define beep scale and pronunciation time */

    struct {
        int fs;       /* frequency */
        int time;     /* Pronunciation time[ms] */
    }
            note[] = {
            {262, 500},
            {294, 500},
            {330, 500},
            {349, 500},
            {392, 500},
            {440, 500},
            {494, 500},
            {523, 1000},
            {523, 500},
            {494, 500},
            {440, 500},
            {392, 500},
            {349, 500},
            {330, 500},
            {294, 500},
            {262, 1000},
            {0,0}
    },
            *p_note;

    /* Set I/O parameters for power on. */

    if (!app_power_on())
    {
        printf("Error: app_power_on() failure.\n");
        return 1;
    }

    /* Cancel output mute. */

    if (board_external_amp_mute_control(false) != OK)
    {
        printf("Error: board_external_amp_mute_control(false) failuer.\n");
        return 1;
    }

    printf("Start AudioBeep example\n");

    for (p_note = note; p_note->fs; p_note++)
    {
        /* Set beep. */

        if (!app_beep(1, -40, p_note->fs))
        {
            break;
        }
        usleep(p_note->time * 1000L);
    }

    /* Beep off. */

    if (!app_beep(0, 255, 0))
    {
        printf("Error: app_beep() failuer.\n");
        return 1;
    }

    /* Set output mute. */

    if (board_external_amp_mute_control(true) != OK)
    {
        printf("Error: board_external_amp_mute_control(true) failuer.\n");
        return 1;
    }

    printf("Stop  AudioBeep example\n");

    /* Set I/O parameters for power off. */

    if (!app_power_off())
    {
        printf("Error: app_power_off() failure.\n");
        return 1;
    }

    printf("Exit  AudioBeep example\n");

    return 0;
}
