# Generated by Django 5.0.6 on 2024-06-21 10:21

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Custom_user', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='ReferenceAmount',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('amount', models.IntegerField()),
            ],
        ),
        migrations.RemoveField(
            model_name='student',
            name='has_access_two',
        ),
    ]
