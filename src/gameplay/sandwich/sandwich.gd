extends CharacterBody2D

@export var speed = 250


func _ready():
	get_node("/root/dangers_manager").generate_dangers(self)


func _process(delta):
	var velocity: Vector2 = Vector2(-1, 0)
	translate(speed * velocity * delta)


func _on_visibility_notifier_screen_exited():
	queue_free()


func add_danger(danger, danger_global_position):
	$dangers.add_child(danger)
	danger.global_position = danger_global_position
