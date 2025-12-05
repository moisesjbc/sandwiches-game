extends Node2D

class_name DangersManager


var initialized: bool = false

var _dangers = [
	{ "scene": preload("res://gameplay/dangers/fire/fire.tscn"), "width": null },
	{ "scene": preload("res://gameplay/dangers/knife/knife.tscn"), "width": null }
]

func _ready():
	for danger in _dangers:
		var danger_instance = danger["scene"].instantiate()
		var danger_baseline = danger_instance.get_node("baseline")
		danger["width"] = danger_baseline.points[1].x - danger_baseline.points[0].x
		
	_dangers.sort_custom(func(a, b): return a["width"] > b["width"])

func get_middle_point(baseline: Line2D):
	return Vector2((baseline.points[0].x + baseline.points[1].x) / 2, (baseline.points[0].y + baseline.points[1].y) / 2)

func baseline_width(baseline: Line2D):
	return int(baseline.points[1].x - baseline.points[0].x)

func generate_dangers(sandwich):
	var first_available_danger_index = 0
	var sandwich_baseline: Line2D = sandwich.get_node("baseline").duplicate()
	
	while first_available_danger_index < len(_dangers):
		var sandwich_point = sandwich_baseline.points[0]
		
		var new_danger_index = randi() % (len(_dangers) - first_available_danger_index) + first_available_danger_index
		var new_danger = _dangers[new_danger_index]["scene"].instantiate()
		var danger_point = new_danger.get_node("baseline").points[0]
		
		var danger_global_position = sandwich.global_position + sandwich_point - danger_point
		sandwich.add_danger(new_danger, danger_global_position)
		
		var danger_width = baseline_width(new_danger.get_node("baseline"))
		var margin = randi() % (danger_width / 2) + (danger_width / 2)
		sandwich_baseline.points[0].x += danger_width + margin
		var sandwich_baseline_width = baseline_width(sandwich_baseline)

		while (first_available_danger_index < len(_dangers) and (sandwich_baseline_width < _dangers[first_available_danger_index]["width"])):
			first_available_danger_index += 1
