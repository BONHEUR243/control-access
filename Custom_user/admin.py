from django.contrib import admin
from .models import User,Departement, Option, Session, Intake, Level, Student, AdminStudent, Supervisor
from students_admins.models import Exam, ExamStatus

admin.site.register(Departement)
admin.site.register(Option)
admin.site.register(Session)
admin.site.register(Intake)
admin.site.register(Level)
admin.site.register(Student)
admin.site.register(AdminStudent)
admin.site.register(Supervisor)
admin.site.register(User) 
admin.site.register(Exam)
admin.site.register(ExamStatus)

  
 





