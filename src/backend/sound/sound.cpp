#include "sound.hpp"

Sound::Sound(const std::filesystem::path &path)
{
    ma_decoder_config cfg = ma_decoder_config_init(m_format, 0, 0);
    ma_decoder decoder;
    ma_decoder_init_file(path.string().c_str(), &cfg, &decoder);

    ma_decoder_get_length_in_pcm_frames(&decoder, &m_frameCount);
    m_channels = decoder.outputChannels;

    ma_uint32 bytesPerFrame =
        ma_get_bytes_per_frame(decoder.outputFormat, decoder.outputChannels);

    p_data = (void *)malloc(m_frameCount * bytesPerFrame);
    ma_decoder_read_pcm_frames(&decoder, p_data, m_frameCount, NULL);

    ma_decoder_uninit(&decoder);
}
Sound::~Sound()
{
    if (p_data)
    {
        free(p_data);
    }
}
