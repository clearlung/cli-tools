c.fonts.default_family = "terminus"
config.load_autoconfig()
config.set("colors.webpage.preferred_color_scheme", "dark")
config.bind(',a', 'hint links spawn --detach mpv {hint-url}')
config.bind(',A', 'hint links spawn --detach mpv --no-video {hint-url}')
