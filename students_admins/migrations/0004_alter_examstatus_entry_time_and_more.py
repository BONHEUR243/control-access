# Generated by Django 5.0.6 on 2024-06-25 15:07

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('students_admins', '0003_alter_examstatus_entry_time_and_more'),
    ]

    operations = [
        migrations.AlterField(
            model_name='examstatus',
            name='entry_time',
            field=models.DateTimeField(default='-', null=True),
        ),
        migrations.AlterField(
            model_name='examstatus',
            name='exit_time',
            field=models.DateTimeField(default='-', null=True),
        ),
    ]