extends Node


func set_health(health: int):
	$gui/margin_container/hbox_container/health_texture/health_label.text = "%03d" % health
