library(hexSticker)

imgurl <- system.file("/data-raw/runner.png", package="fasterr")
sticker(imgurl, package="fasterr",
        p_size=7, 
        p_color="#ED217C",  # Text color (package name)
        h_fill= "#FFD9DA",    # Background color of the hex sticker
        h_color="#ED217C",  # Border color of the hex sticker
        s_x=1, 
        s_y=.75, 
        s_width=0.6,
        filename="data-raw/fasterr.png")