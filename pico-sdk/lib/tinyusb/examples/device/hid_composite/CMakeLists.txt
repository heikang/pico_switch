cmake_minimum_required(VERSION 3.5)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../../hw/bsp/${FAMILY}/family.cmake)

# gets PROJECT name for the example (e.g. <BOARD>-<DIR_NAME>)
family_get_project_name(PROJECT ${CMAKE_CURRENT_LIST_DIR})

project(${PROJECT})

# Checks this example is valid for the family and initializes the project
family_initialize_project(${PROJECT} ${CMAKE_CURRENT_LIST_DIR})

add_executable(${PROJECT})

# Example source
target_sources(${PROJECT} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core1.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_descriptors.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_18.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_28.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_simsun_16_cjk.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_22.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_10.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_42.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_26.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_34.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_16.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_unscii_16.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_20.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_32.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_40.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_38.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_28_compressed.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_24.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_12_subpx.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_44.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_unscii_8.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_12.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_30.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_loader.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_14.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_46.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_fmt_txt.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_8.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_36.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/font/lv_font_montserrat_48.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_mask.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_label.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_img_cache.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_line.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_img_decoder.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_arc.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_triangle.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_blend.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_img.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_img_buf.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/draw/lv_draw_rect.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/gpu/lv_gpu_nxp_vglite.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/gpu/lv_gpu_nxp_pxp.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/gpu/lv_gpu_stm32_dma2d.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/gpu/lv_gpu_nxp_pxp_osa.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_bar.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_arc.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_table.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_btn.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_line.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_dropdown.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_textarea.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_objx_templ.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_canvas.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_checkbox.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_btnmatrix.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_switch.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_label.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_roller.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_slider.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/widgets/lv_img.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj_style_gen.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj_pos.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_theme.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_event.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj_class.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj_style.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj_tree.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj_draw.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_disp.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_group.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_indev.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_refr.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_obj_scroll.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/core/lv_indev_scroll.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_printf.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_txt_ap.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_txt.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_style.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_gc.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_style_gen.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_tlsf.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_async.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_math.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_utils.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_ll.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_timer.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_bidi.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_anim.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_log.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_color.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_fs.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_mem.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_area.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/misc/lv_templ.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/hal/lv_hal_tick.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/hal/lv_hal_disp.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/hal/lv_hal_indev.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/lv_extra.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/tabview/lv_tabview.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/chart/lv_chart.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/meter/lv_meter.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/led/lv_led.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/spinner/lv_spinner.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/win/lv_win.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/keyboard/lv_keyboard.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/tileview/lv_tileview.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/msgbox/lv_msgbox.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/span/lv_span.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/list/lv_list.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/animimg/lv_animimg.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/calendar/lv_calendar.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/widgets/spinbox/lv_spinbox.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/layouts/flex/lv_flex.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/layouts/grid/lv_grid.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/themes/default/lv_theme_default.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/themes/mono/lv_theme_mono.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl/src/extra/themes/basic/lv_theme_basic.c
	)

# Example include
target_include_directories(${PROJECT} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

# Configure compilation flags and libraries for the example... see the corresponding function
# in hw/bsp/FAMILY/family.cmake for details.
family_configure_device_example(${PROJECT})
