# Generated by Django 5.0.6 on 2024-06-25 13:54

import django.db.models.deletion
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Custom_user', '0008_remove_message_receiver_message_receivers'),
        ('students_admins', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='ExamStatus',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('entry_time', models.DateTimeField(blank=True, null=True)),
                ('exit_time', models.DateTimeField(blank=True, null=True)),
                ('status', models.CharField(default='Absent', max_length=20)),
                ('exam', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='students_admins.exam')),
                ('student', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='Custom_user.student')),
            ],
        ),
    ]